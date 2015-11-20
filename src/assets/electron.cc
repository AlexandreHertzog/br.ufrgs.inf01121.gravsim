#include "electron.hh"

#include "util.hh"

using std::vector;

using namespace GravSim::Assets;
using GravSim::Assets::Particle;
using GravSim::Util::ApplyToAll;

Electron::Electron(
  const vector<double> position, const size_t size,
  const vector<float> color, const vector<double> velocity,
  const double charge
)
  : Particle(position, size, color, velocity), _charge(charge)
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

void Electron::ApplyForce(const vector<double> force) {
  // force = mass * accel
  // accel = force / mass
  const vector<double> accel = {
    force[0] / 100,
    force[1] / 100
  };
  // velocity = accel * time, time = 1/1000
  ApplyToAll(_velocity, [&](size_t i) {_velocity[i] += accel[i]/1000;});
  ApplyToAll(_position, [&](size_t i) {_position[i] += _velocity[i];}); 
}
