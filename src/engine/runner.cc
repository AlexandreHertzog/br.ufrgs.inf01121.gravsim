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

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Runner::Runner(const wxString &title)
	: Window(title), _storage(new Storage()),
        _exec(new thread(&Runner::Execute, this))
{
  // We create an instance of Storage here to declutter the Window class.
  Window::SetCanvas(unique_ptr<Canvas>(new Canvas(_storage, this)));

  _simphase = Phase::RUNNING;
  _isrunning = true;
}

Runner::~Runner(void) {
  _isrunning = false;
  _exec->join();
}

void Runner::Execute(void) {
  while (_isrunning) {
    if (_simphase == Phase::PAUSED) {
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
  using GravSim::Assets::Particle;

  shared_ptr<Particle> particle, other_particle;
  vector<double> distvec, forcevec;

  for (size_t i = 0; (particle = _storage->GetParticle(i)) != NULL; i++) {
    auto gravfield = particle->GetGravField();
    for (size_t j = i + 1; (other_particle = _storage->GetParticle(j)) != NULL; j++) {
      // This is the dumb version: we need to manually calculate the force vector.
      double force = gravfield(other_particle->GetMass(), other_particle->GetPosition());
      distvec= {
      	particle->GetPosition()[0] + other_particle->GetPosition()[0],
      	particle->GetPosition()[1] + other_particle->GetPosition()[1]
      };
      distvec= NormaliseVector(distvec);
      forcevec= {force * distvec[0], force * distvec[1]};
			
      particle->ApplyForce(forcevec);
      other_particle->ApplyForce(forcevec);
    }
  }
}
