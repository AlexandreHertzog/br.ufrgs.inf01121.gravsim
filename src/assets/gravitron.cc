#include "gravitron.hh"

#include <algorithm>
#include <cmath>

#include "../util.hh"

using namespace GravSim::Assets;
using GravSim::Util::ApplyToAll;

Gravitron::Gravitron(
  const vector<double> position, const double size,
  const double mass, const vector<double> velocity
)
  : Point(position, size)
{
  _mass = mass;
  _velocity = velocity;
}

Gravitron::~Gravitron(void) {
}

double Gravitron::GetMass(void) {
  return _mass;
}

std::function<double(double, vector<double>)> Gravitron::GetGravField(void) {
  return [&](double m2, vector<double> p2) {
    return FORCEFORMULA(_mass, m2, _position, p2);
  };
}

void Gravitron::ApplyForce(const vector<double> force) {
  // force = mass * accel
  // accel = force / mass
  vector<double> accel;
  const double mass = _mass;
  ApplyToAll(force, [&accel, force, mass](size_t i) {accel.push_back(force[i] / mass);});
  // velocity = accel * time
  ApplyToAll(_velocity, [&](size_t i) {_velocity[i] += accel[i]/1000;});
  vector<double> pos = _position;
  const vector<double> vel = _velocity;
  ApplyToAll(pos, [vel, &pos] (size_t i) {pos[i] += vel[i];});
  _position = pos;
}
