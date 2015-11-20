#include "gravitron.hh"

#include <algorithm>
#include <cmath>

#include "../util.hh"

using std::vector;
using namespace GravSim::Assets;
using GravSim::Util::ApplyToAll;

Gravitron::Gravitron(
  const vector<double> position, const double size,
  const vector<double> velocity, const double mass
)
  : Particle(position, size, velocity)
{
  _mass = mass;
}

Gravitron::~Gravitron(void) {
}

double Gravitron::GetValue(void) const {
  return _mass;
}

std::function<double(double, vector<double>)> Gravitron::GetField(void) const {
  const double mass = _mass;
  const std::vector<double> pos = _position;

  return [mass, pos](double m2, vector<double> p2) {
    return GFORCE(mass, m2, pos, p2);
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
