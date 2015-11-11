#include "runner.hh"

#include "canvas.hh"
#include "util.hh"
#include "logger.hh"

using namespace GravSim::Engine;

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Runner::Runner(const wxString &title)
	: Window(title), _storage(new Storage())
{
  // We create an instance of Storage here to declutter the Window class.
  using GravSim::Gui::Canvas;
  Window::SetCanvas(unique_ptr<Canvas>(new Canvas(_storage, this)));

  _simphase = Phase::RUNNING;
}

Runner::~Runner(void) {
}

void Runner::Execute(void) {
  while (true) {
    if (_simphase == Phase::STOPPED) {
      return;
    }
    StepSimulation();
    if (_simphase == Phase::STEPPED) {
      return;
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

void Runner::StepSimulation(void) {
  using GravSim::Assets::Particle;

  shared_ptr<Particle> particle, other_particle;
  vector<double> distvector;

  std::function<vector<double>(vector<double>)> normalise_vector = [] (vector<double> vec) {
    double sumofparts = 0;
    std::function<void(size_t)> operation = [&sumofparts, vec] (size_t i) {
      sumofparts += pow(vec[i], 2);
    };
    GravSim::Util::ApplyToAll(vec, operation);
    double magnitude = sqrt(sumofparts);
    operation = [&vec, magnitude] (size_t i) {
      vec[i] = vec[i] / magnitude;
    };
    GravSim::Util::ApplyToAll(vec, operation);
    return vec;
  };

  vector<double> forcevector;
  for (size_t i = 0; (particle = _storage->GetParticle(i)) != NULL; i++) {
    auto gravfield = particle->GetGravField();
    for (size_t j = i + 1; (other_particle = _storage->GetParticle(j)) != NULL; j++) {
      // This is the dumb version: we need to manually calculate the force vector.
      double force = gravfield(other_particle->GetMass(), other_particle->GetPosition());
      distvector = {
      	particle->GetPosition()[0] + other_particle->GetPosition()[0],
      	particle->GetPosition()[1] + other_particle->GetPosition()[1]
      };
      distvector = normalise_vector(distvector);
      forcevector = {force * distvector[0], force * distvector[1]};
			
      particle->ApplyForce(forcevector);
      other_particle->ApplyForce(forcevector);
    }
  }
}
