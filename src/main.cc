#include "main.h"

#include "window.h"

IMPLEMENT_APP(GravSimApp)

bool GravSimApp::OnInit(void) {
  GravSimGui::Window *win = new GravSimGui::Window(wxT(
    "Simulador Gravitacional"
  ));
  win->Show(true);
  
  return true;
}
