#include "main.h"

#include "runner.hh"

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

IMPLEMENT_APP(GravSimApp)

bool GravSimApp::OnInit(void) {
	
  GravSim::Engine::Runner *win = new GravSim::Engine::Runner(wxT(
    "Simulador Gravitacional"
  ));
  win->Show(true);
  return true;
}
