#include "main.h"

#include <memory>

#include "window.hh"
#include "storage.hh"
#include "logger.hh"

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

IMPLEMENT_APP(GravSimApp)

bool GravSimApp::OnInit(void) {
<<<<<<< HEAD
=======
	//GravSim::Engine::Logger *log = new GravSim::Engine::Logger();
	GravSim::Engine::Logger::LoggerInit();
>>>>>>> logger-class
  std::unique_ptr<GravSim::Engine::Storage> storage(
    new GravSim::Engine::Storage()
  );
  GravSim::Gui::Window *win = new GravSim::Gui::Window(std::move(storage), wxT(
    "Simulador Gravitacional"
  ));
  win->Show(true);
  return true;
}
