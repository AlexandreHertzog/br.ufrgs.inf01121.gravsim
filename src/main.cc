#include "main.h"

#include "window.hh"

/* Unfortunately, this is necessary. g++ points out many warning about internal
 * wxGLCanvas functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

IMPLEMENT_APP(GravSimApp)

bool GravSimApp::OnInit(void) {
  GravSim::Gui::Window *win = new GravSim::Gui::Window(wxT(
    "Simulador Gravitacional"
  ));
  win->Show(true);
  
  return true;
}
