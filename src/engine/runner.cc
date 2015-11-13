#include "runner.hh"

#include <thread>

#include "canvas.hh"
#include "util.hh"
#include "logger.hh"

using namespace GravSim::Engine;
using std::shared_ptr;
using std::unique_ptr;
using std::function;
using std::thread;

using GravSim::Gui::Canvas;
using GravSim::Util::NormaliseVector;
using GravSim::Util::NumTimesVec;
using GravSim::Util::VecPlusVec;
using GravSim::Assets::Particle;

using GravSim::Exception::BadIndex;
using GravSim::Exception::BadNewFile;
using GravSim::Exception::BadFileLoad;

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Runner::Runner(const wxString &title)
	: Window(title), _storage(new Storage()), _isrunning(true),
        _exec(new thread(&Runner::Execute, this))
{
  // We create an instance of Storage here to declutter the Window class.
  Window::SetCanvas(unique_ptr<Canvas>(new Canvas(_storage, this)));

  _simphase = Phase::RUNNING;
}

Runner::~Runner(void) {
  _isrunning = false;
  _exec->join();
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
    _storage->LoadParticlesFromFile(filename);
  } catch (const BadFileLoad badload) {
  }
}

void Runner::GenerateRandom(const size_t numparticles) {
  try {
    _storage->GenerateRandom(10);
  } catch (const BadNewFile badnew) {
  }
}

const std::string Runner::GetFilename(void) {
  return _storage->GetFilename();
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
  _simphase = Phase::PAUSED;
}

void Runner::OnStep(wxCommandEvent &WXUNUSED(event)) {
  Logger::LogInfo(*this, "Stepping simulation.");
  StepSimulation();
}

void Runner::StepSimulation(void) {
  try {
    size_t numparticles = _storage->GetNumParticles();
    for (size_t i = 0; i < numparticles; i++) {
      for (size_t j = i + 1; j < numparticles; j++) {
        shared_ptr<Particle> p1 = _storage->GetParticle(i);
        shared_ptr<Particle> p2 = _storage->GetParticle(j);

        auto p1field = p1->GetGravField();
        double force = p1field(p2->GetMass(), p2->GetPosition());

        vector<double> distance = {
          p1->GetPosition()[0] - p2->GetPosition()[0],
          p1->GetPosition()[1] - p2->GetPosition()[1]
        };
        distance = NormaliseVector(distance);
        if (force > 10) {
          force = 10;
        }
        force *= SPEEDFACTOR;
        vector<double> forcevec = NumTimesVec(force, distance);
        p2->ApplyForce(forcevec);
        forcevec = NumTimesVec(-force, distance);
        p1->ApplyForce(forcevec);
      }
    }
  } catch (const BadIndex except) {
    std::cout << "ops" << std::endl;
    _simphase = Phase::PAUSED;
  }
}
