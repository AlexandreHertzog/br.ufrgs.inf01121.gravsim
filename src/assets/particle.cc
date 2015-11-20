#include "particle.hh"

using std::vector;
using namespace GravSim::Assets;

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
