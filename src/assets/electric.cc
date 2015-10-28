#include "electric.hh"

using namespace GravSim::Assets;

Electric::Electric(
  const double charge, const double mass, const double *velocity, 
  const double *position, const size_t size
)
  : Particle(mass, velocity, position, size)
{
  _charge = charge;
}

Electric::~Electric(void) {
}

double Electric::GetCharge(void) {
  return _charge;
}
