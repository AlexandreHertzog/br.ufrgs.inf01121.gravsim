// Copied from https://wiki.wxwidgets.org/WxGLCanvas

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/statusbr.h>

#include <memory>

#include "canvas.hh"
#include "storage.hh"

namespace GravSim{
namespace Gui {

const int ID_ADD_PART = 0;
const int ID_PAUSE = 1;
const int ID_RESUME = 2;
const int ID_STOP = 3;
const int ID_STEP = 4;

class Window : public wxFrame {
public:
  // Constructor and destructor.
  Window(std::shared_ptr<GravSim::Engine::Storage> storage, const wxString &title);
  ~Window(void);
  void SetText(const wxString string);

private:
  // Connection functions.
  void OnQuit(wxCommandEvent &event);
  void OnNew(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  
  void OnAddParticle(wxCommandEvent &event);
  
  void OnPause(wxCommandEvent &event);
  void OnResume(wxCommandEvent &event);
  void OnStop(wxCommandEvent &event);
  void OnStep(wxCommandEvent &event);
  
  // Internal variables.
  // 'menubar' is the bar below the window title bar.
  wxMenuBar *_menubar;
  // Below, the menus that will be embedded inside the 'menubar'.
  wxMenu    *_filemenu;
  wxMenu    *_editmenu;
  wxMenu    *_simmenu;
  // Canvas is the middle class between the interface and the OpenGL canvas.
  Canvas    *_canvas;

  std::shared_ptr<GravSim::Engine::Storage> _storage;
  
  //wxStatusBar *_statusbar;
}; // class Window
}; // namespace Gui
}; // namespace GravSim
