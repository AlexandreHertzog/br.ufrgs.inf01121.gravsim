#include <algorithm>

#include "particle.hh"

using namespace GravSim::Assets;

Particle::Particle(void) {
}

Particle::Particle(
  const double mass, const double *vel, const double *pos
) {
  _mass = mass;
  std::copy(pos, pos + NUM_DIMENSIONS, _pos);
  std::copy(vel, vel + NUM_DIMENSIONS, _vel);
}

double Particle::GetMass(void) {
  return _mass;
}

void Particle::GetPos(double *out) {
  std::copy(_pos, _pos + NUM_DIMENSIONS, out);
}

void Particle::GetVel(double *out) {
  std::copy(_vel, _vel + NUM_DIMENSIONS, out);
}

void Particle::ApplyForce(const double *force) {
  /* To calculate the new speed, there are two concepts being used:
   * momentum = mass * velocity => velocity = momentum / mass
   * variation in momentum = force * (variation in time)
   * Since this apply force function evaluates the step of the simulation, we
   * consider the variation in time equals 1. So:
   * velocity = momentum / mass = force * 1 / mass = force / mass
   * TODO: Check the actual integrity of these conclusions. */
  for (int i = 0; i < NUM_DIMENSIONS; i++) {
    _vel[i] = force[i] / _mass;
  }
}

void Particle::StepPosition(void) {
  for (int i = 0; i < NUM_DIMENSIONS; i++) {
    _pos[i] += _vel[i];
  }
}
