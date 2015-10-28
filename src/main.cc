#include "main.h"

#include "window.hh"

IMPLEMENT_APP(GravSimApp)

bool GravSimApp::OnInit(void) {
  GravSim::Gui::Window *win = new GravSim::Gui::Window(wxT(
    "Simulador Gravitacional"
  ));
  win->Show(true);
  
  return true;
}
