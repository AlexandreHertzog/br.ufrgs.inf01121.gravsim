#include <algorithm>
#include <cmath>

#include "gravitron.hh"

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

	return [posx, posy, mymass](double mass, vector<double> pos){
		double field = GRAVCONSTANT * mymass * mass;
		double incomplete_distance =
			pow(posx - pos[0], 2) + pow(posy - pos[0], 2);
		field = field / incomplete_distance;
		return field;
	};
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
