#include "gravitron.hh"

#include <algorithm>
#include <cmath>

#include "../util.hh"

using namespace GravSim::Assets;

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
  // Let's avoid some statics.
  const double posx = _position[0];
  const double posy = _position[1];
  const double mymass = _mass;

  return [posx, posy, mymass](double mass, vector<double> pos) {
    double field = GRAVCONSTANT * mymass * mass;
    double incomplete_distance = pow(posx - pos[0], 2) + pow(posy - pos[0], 2);
    field = field / incomplete_distance;
    return field;
  };
}

void Gravitron::ApplyForce(const vector<double> force) {
  // force = mass * accel
  // accel = force / mass
  vector<double> accel;
  const double mass = _mass;
  std::function<void(size_t)> applyforce = [&accel, force, mass](size_t i) {
    accel.push_back(force[i] / mass);
  };
  GravSim::Util::ApplyToAll(force, applyforce);
  // velocity = accel * time
  // Time is not needed, since this is updated on every step.
  _velocity = accel;
  vector<double> pos = _position;
  const vector<double> vel = _velocity;
  std::function<void(size_t)> incpos = [vel, &pos] (size_t i) {
    pos[i] += vel[i];
  };
  GravSim::Util::ApplyToAll(pos, incpos);
}
