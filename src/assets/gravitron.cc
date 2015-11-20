#include "gravitron.hh"

#include "../util.hh"

using std::vector;
using namespace GravSim::Assets;
using GravSim::Util::ApplyToAll;

Gravitron::Gravitron(
  const vector<double> position, const size_t size,
  const vector<double> velocity, const double mass
)
  : Particle(position, size, velocity), _mass(mass)
{
}

double Gravitron::GetValue(void) const {
  return _mass;
}

std::function<double(double, vector<double>)> Gravitron::GetField(void) const {
  const double mass = _mass;
  const std::vector<double> pos = _position;
  const auto forcefun = FORCE;
  const double constant = GCONSTANT;

  return [mass, pos, forcefun, constant](double m2, vector<double> p2) {
    return forcefun(constant, mass, m2, pos, p2);
  };
}
