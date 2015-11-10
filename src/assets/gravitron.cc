#include <algorithm>

#include "gravitron.hh"

using namespace GravSim::Assets;

Gravitron::Gravitron
(
  const double mass, const double *velocity, const double *position,
  const size_t size
)
  : Point(position, size)
{
  _mass = mass;
  std::copy(velocity, velocity + NUM_DIMENSIONS, _velocity);
}

Gravitron::~Gravitron(void) {
}

double Gravitron::GetMass(void) {
  return _mass;
}

void Gravitron::ApplyForce(const double *force) {
  /* To calculate the new speed, there are two concepts being used:
   * momentum = mass * velocity => velocity = momentum / mass
   * variation in momentum = force * (variation in time)
   * Since this apply force function evaluates the step of the simulation, we
   * consider the variation in time equals 1. So:
   * velocity = momentum / mass = force * 1 / mass = force / mass
   * TODO: Check the actual integrity of these conclusions. */
  for (int i = 0; i < NUM_DIMENSIONS; i++) {
    _velocity[i] = force[i] / _mass;
  }
}

void Gravitron::StepPosition(void) {
  IncrementPosition(_velocity);
}
