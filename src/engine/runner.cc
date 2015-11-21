#include "runner.hh"

#include <thread>

#include "canvas.hh"
#include "util.hh"
#include "logger.hh"
#include "gravitron.hh"
#include "cmake_defines.hh"

using namespace GravSim::Engine;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::function;
using std::thread;

using GravSim::Assets::Particle;
using GravSim::Assets::Gravitron;

using GravSim::Exception::BadIndex;
using GravSim::Exception::BadNewFile;
using GravSim::Exception::BadFileLoad;

using GravSim::Gui::Canvas;

using GravSim::Util::NormaliseVector;
using GravSim::Util::NumTimesVec;
using GravSim::Util::VecPlusVec;

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Runner::Runner(const wxString &title)
  : Window(title), _storage(new Storage())
{
  // We create an instance of Storage here to declutter the Window class.
  Window::SetCanvas(unique_ptr<Canvas>(new Canvas(_storage, this)));

  _simphase = Phase::RUNNING;
  //InitResults(1);
  StartThread();

#ifdef _OPENMP_ENABLED_
  Logger::LogInfo(*this, "OpenMP is enabled!");
#else
  Logger::LogInfo(*this, "OpenMP is not enabled. It was not found during compile.");
#endif
}

Runner::~Runner(void) {
  StopThread();
}

void Runner::Execute(void) {
  Logger::LogInfo(*this, "Starting thread.");
  while (_isrunning) {
    std::this_thread::sleep_for(std::chrono::milliseconds(long(UPDATEFREQ)));
    Window::UpdateCanvas();
    if (_simphase == Phase::PAUSED) {
      continue;
    }
    StepSimulation();
    if (_simphase == Phase::STEPPED) {
      _simphase = Phase::PAUSED;
      continue;
    }
    if (_simphase == Phase::RUNNING) {
      continue;
    }
  }
}

const std::string Runner::GetObjName(void) const {
  return "GravSim::Engine::Runner";
}

void Runner::SaveParticlesToFile(const std::string filename) {
  _storage->SaveParticlesToFile(filename);
}

void Runner::LoadParticlesFromFile(const std::string filename) {
  try {
    StopThread();
    ClearResults();
    _partcount = _storage->LoadParticlesFromFile(filename);
    InitResults();
    StartThread();
  } catch (const BadFileLoad badload) {
  }
}

void Runner::GenerateRandom(const size_t numparticles) {
  try {
    StopThread();
    ClearResults();
    _partcount = numparticles;
    _storage->GenerateRandom(_partcount);
    InitResults();
    StartThread();
  } catch (const BadNewFile badnew) {
  }
}

const std::string Runner::GetFilename(void) {
  return _storage->GetFilename();
}

void Runner::AddParticle(const vector<double> params) {
  double mass = 0.0, posx = 0.0, posy = 0.0;
  try {
    mass = params[0];
    posx = params[1];
    posy = params[2];
  } catch(...) {
  }

  const size_t size = mass/10;

  shared_ptr<Particle> part(new Gravitron({posx, posy}, size, {1.0, 1.0, 1.0}, {0.0, 0.0}, mass));
  _storage->AppendParticle(part);
}

void Runner::OnPause(wxCommandEvent &WXUNUSED(event)) {
  Logger::LogInfo(*this, "Pausing simulation.");
  _simphase = Phase::PAUSED;
}

void Runner::OnResume(wxCommandEvent &WXUNUSED(event)) {
  Logger::LogInfo(*this, "Resuming simulation.");
  _simphase = Phase::RUNNING;
}

void Runner::OnStop(wxCommandEvent &WXUNUSED(event)) {
  Logger::LogInfo(*this, "Stopping simulation.");
  StopThread();
  _storage->ClearParticles();
  StartThread();
  _simphase = Phase::PAUSED;
}

void Runner::OnStep(wxCommandEvent &WXUNUSED(event)) {
  Logger::LogInfo(*this, "Stepping simulation.");
  _simphase = Phase::STEPPED;
}

void Runner::StepSimulation(void) {
  const vector<double> invalid_force = {0.0, 0.0};
  try {
    size_t numparticles = _storage->GetNumParticles();
#ifdef _OPENMP_ENABLED_
#pragma omp parallel for schedule(dynamic)
#endif
    for (size_t i = 0; i < numparticles; i++) {
      for (size_t j = 0; j < numparticles; j++) {
        if (j == i) {
          _resultmatrix[i][j] = {0.0, 0.0};
          continue;
        }
        if (_resultmatrix[j][i] != invalid_force) {
          _resultmatrix[i][j] = NumTimesVec(-1, _resultmatrix[j][i]);
          continue;
        }
        shared_ptr<Particle> p1 = _storage->GetParticle(i);
        shared_ptr<Particle> p2 = _storage->GetParticle(j);

        auto p1field = p1->GetField();
        double force = p1field(p2->GetValue(), p2->GetPosition());
        force *= SPEEDFACTOR;

        vector<double> distance = {
          p1->GetX() - p2->GetX(), p1->GetY() - p2->GetY()
        };
        distance = NormaliseVector(distance);
        vector<double> forcevec = NumTimesVec(force, distance);
        _resultmatrix[i][j] = forcevec;
      }
    }
#ifdef _OPENMP_ENABLED_
#pragma omp parallel for schedule(dynamic)
#endif
    for (size_t i = 0; i < numparticles; i++) {
      shared_ptr<Particle> p = _storage->GetParticle(i);
      for (size_t j = 0; j < numparticles; j++) {
        if (i == j) {
          continue;
        }
        p->ApplyForce(_resultmatrix[i][j]);
        _resultmatrix[i][j] = {0.0, 0.0};
      }
    }
  } catch (const BadIndex except) {
    _simphase = Phase::PAUSED;
  }
}

void Runner::StopThread(void) {
  _isrunning = false;
  _exec->join();
}

void Runner::StartThread(void) {
  _isrunning = true;
  _exec = std::move(unique_ptr<thread>(new thread(&Runner::Execute, this)));
}

void Runner::ClearResults(void) {
  for (int i = 0; i < _partcount; i++) {
    for (int j = 0; j < _partcount; j++) {
      _resultmatrix[i][j].clear();
    }
    delete[] _resultmatrix[i];
  }
  if (_partcount > 0) {
    delete[] _resultmatrix;
  }
}

void Runner::InitResults(void) {
  _resultmatrix = new vector<double>*[_partcount];
  for (int i = 0; i < _partcount; i++) {
    _resultmatrix[i] = new vector<double>[_partcount];
    for (int j = 0; j < _partcount; j++) {
      _resultmatrix[i][j] = {0.0, 0.0};
    }
  }
}
