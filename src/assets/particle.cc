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

vector<double> Particle::GetVelocity(void) {
  return _velocity;
}


