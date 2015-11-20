#include "particle.hh"

using std::vector;

using namespace GravSim::Assets;
using GravSim::Util::ApplyToAll;

Particle::Particle(
  const vector<double> position, const size_t size,
  const vector<double> velocity
)
  : Point(position, size)
{
  _velocity = velocity;
}

Particle::~Particle(void) {
}

vector<double> Particle::GetVelocity(void) {
  return _velocity;
}

void Particle::ApplyForce(std::vector<double> force, const double mass) {
  // force = mass * accel
  // accel = force / mass
  const vector<double> accel = {
    force[0] / mass,
    force[1] / mass
  };
  // velocity = accel * time, time = 1/1000
  ApplyToAll(_velocity, [&](size_t i) {_velocity[i] += accel[i]/1000;});
  ApplyToAll(_position, [&](size_t i) {_position[i] += _velocity[i];}); 
}

