#include "main.h"

#include <memory>

#include "runner.hh"
#include "storage.hh"
#include "logger.hh"

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

IMPLEMENT_APP(GravSimApp)

bool GravSimApp::OnInit(void) {
	
  std::unique_ptr<GravSim::Engine::Storage> storage(
    new GravSim::Engine::Storage()
  );
  GravSim::Engine::Runner *win = new GravSim::Engine::Runner(std::move(storage), wxT(
    "Simulador Gravitacional"
  ));
  win->Show(true);
  return true;
}
