#include "particle.hh"

using namespace GravSim::Assets;

Particle::Particle(
	const vector<double> position, const size_t size,
	const double mass, const vector<double> velocity,
	const double charge
)
	: Gravitron(position, size, mass, velocity), Electron(charge)
{
}

Particle::Particle(
		const vector<double> position, const size_t size,
		const double mass, const vector<double> velocity
)
	: Gravitron(position, size, mass, velocity), Electron(0)
{
}

Particle::Particle(
		const vector<double> position, const size_t size,
		const double charge
)
	: Gravitron(position, size, 0, {0}), Electron(charge)
{
}

Particle::~Particle(void) {
}
