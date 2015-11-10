#include "runner.hh"

#include "canvas.hh"

using namespace GravSim::Engine;

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Runner::Runner(const wxString &title)
	: Window(title), _storage(new Storage())
{
	unique_ptr<GravSim::Gui::Canvas> canvas(new GravSim::Gui::Canvas(_storage, this));
	Window::SetCanvas(std::move(canvas));
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
