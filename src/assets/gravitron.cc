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

std::function<double(double)> Gravitron::GetGravField(const vector<double> point) {
	double squareddistance = SquareOfDistance(point);
	return [squareddistance](double mass){return GRAVCONSTANT * _mass * mass / squareddistance;};
}

void Gravitron::ApplyForce(const vector<double> force) {
	// TODO: is all this calculation really necessary?
	// force = mass * accel
	// accel = force / mass
	vector<double> accel;
	for (size_t i = 0; i < force.size(); i++) {
		accel.push_back(force[i] / _mass);
	}
}
