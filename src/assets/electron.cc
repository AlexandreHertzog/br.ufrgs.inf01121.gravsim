#include "electron.hh"

#include "util.hh"

using std::vector;

using namespace GravSim::Assets;
using GravSim::Assets::Particle;
using GravSim::Util::ApplyToAll;

Electron::Electron(
  const vector<double> position, const size_t size, const vector<double> velocity,
  const double charge
)
  : Particle(position, size, velocity), _charge(charge)
{
}

double Electron::GetValue(void) const {
  return _charge;
}

std::function<double(double, vector<double>)> Electron::GetField(void) const {
  const double charge = _charge;
  const std::vector<double> pos = _position;
  const auto forcefun = FORCE;
  const double constant = ECONSTANT;

  return [charge, pos, forcefun, constant](double m2, vector<double> p2) {
    return forcefun(constant, charge, m2, pos, p2);
  };
}
