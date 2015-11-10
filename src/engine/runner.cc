#include "runner.hh"

using namespace GravSim::Engine;

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Runner::Runner(shared_ptr<GravSim::Engine::Storage> storage, const wxString &title)
	: Window(storage, title)
{
	_storage = storage;
}

Runner::~Runner(void) {
}

void Runner::Execute(void) {
}

const std::string Runner::GetObjName(void) const {
	return "GravSim::Engine::Runner";
}

void Runner::SavePointsToFile(const std::string filename) {
	_storage->SavePointsToFile(filename);
}

void Runner::LoadPointsFromFile(const std::string filename) {
	_storage->LoadPointsFromFile(filename);
}

void Runner::GenerateRandom(const size_t numparticles) {
	_storage->GenerateRandom(numparticles);
}

const std::string Runner::GetFilename(void) {
	return _storage->GetFilename();
}