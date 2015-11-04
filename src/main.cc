#include "main.h"

#include "window.hh"
#include "storage.hh"

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

IMPLEMENT_APP(GravSimApp)

bool GravSimApp::OnInit(void) {
#ifdef _TEST_RENDER_
  GravSim::Engine::Storage *storage = new GravSim::Engine::Storage();
#else
  // TODO: change this to support file loading.
  GravSim::Engine::Storage *storage = new GravSim::Engine::Storage();
#endif
  GravSim::Gui::Window *win = new GravSim::Gui::Window(storage, wxT(
    "Simulador Gravitacional"
  ));
  win->Show(true);
  
  return true;
}
