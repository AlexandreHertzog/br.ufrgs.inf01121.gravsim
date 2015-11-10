#include "particle.hh"

using namespace GravSim::Assets;

Particle::Particle(
	const vector<double> position, const size_t size,
	const double mass, const vector<double> velocity,
	const double charge
)
	: Point(position, size), Gravitron(mass, velocity), Electron(charge)
{
}

Particle::Particle(
		const vector<double> position, const size_t size,
		const double mass, const vector<double> velocity
)
	: Point(position, size), Gravitron(mass, velocity), Electron(0)
{
}

Particle::Particle(
		const vector<double> position, const size_t size,
		const double charge
)
	: Point(position, size), Gravitron(0, {0}), Electron(charge)
{
}

Particle::~Particle(void) {
}
