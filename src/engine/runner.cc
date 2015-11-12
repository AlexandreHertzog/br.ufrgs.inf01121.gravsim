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
using GravSim::Assets::Particle;

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
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
  _storage->LoadParticlesFromFile(filename);
}

void Runner::GenerateRandom(const size_t numparticles) {
  _storage->GenerateRandom(numparticles);
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
}

void Runner::OnStep(wxCommandEvent &WXUNUSED(event)) {
  Logger::LogInfo(*this, "Stepping simulation.");
  StepSimulation();
}

void Runner::StepSimulation(void) {

  // We use statics to avoid allocing in every single step.
  static vector<double> distvec = {0}, forcevec = {0};
  static size_t i = 0, j = 0;
  static shared_ptr<Particle> particle = nullptr;
  static shared_ptr<Particle> other_particle = nullptr;
  static function<double (double, vector<double>)> gravfield = [] (double, vector<double>) {
    return 0.0;
  };
  static double force = 0;

  i = 0;
  j = 1;
  particle = _storage->GetParticle(0);
  other_particle = _storage->GetParticle(1);

  for (i = 0; (particle); i++) {
    gravfield = particle->GetGravField();
    for (j = i + 1; (other_particle); j++) {
      // This is the dumb version: we need to manually calculate the force vector.
      force = gravfield(other_particle->GetMass(), other_particle->GetPosition());
      force *= 1e10;
      distvec = {
      	particle->GetPosition()[0] + other_particle->GetPosition()[0],
      	particle->GetPosition()[1] + other_particle->GetPosition()[1]
      };
      distvec = NormaliseVector(distvec);
      forcevec = {force * distvec[0], force * distvec[1]};
			
      particle->ApplyForce(forcevec);
      other_particle->ApplyForce(forcevec);
      other_particle = _storage->GetParticle(j);
    }
    particle = _storage->GetParticle(i);
  }
}
