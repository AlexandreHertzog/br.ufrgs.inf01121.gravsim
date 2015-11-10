#include <algorithm>

#include "gravitron.hh"

using namespace GravSim::Assets;

Gravitron::Gravitron(const double mass, const vector<double> velocity) {
  _mass = mass;
  _velocity = velocity;
}

Gravitron::~Gravitron(void) {
}

double Gravitron::GetMass(void) {
  return _mass;
}

