#include "runner.hh"

using namespace GravSim::Engine;

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Runner::Runner(unique_ptr<GravSim::Engine::Storage> storage, const wxString &title)
	: Window(std::move(storage), title)
{

}

Runner::~Runner(void) {
}

void Runner::Execute(void) {
}

const std::string Runner::GetObjName(void) const {
}
