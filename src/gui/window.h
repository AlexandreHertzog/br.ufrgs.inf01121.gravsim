// Copied from https://wiki.wxwidgets.org/WxGLCanvas

#include <wx/wx.h>
#include <wx/menu.h>

#include "canvas.h"

namespace GravSimGui {
class Window : public wxFrame {
public:
  // Constructor and destructor.
  Window(const wxString &title);

private:
  // Connection functions.
  void OnQuit(wxCommandEvent &event);
  void OnNew(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  
  // Internal variables.
  // 'menubar' is the bar below the window title bar.
  wxMenuBar *menubar;
  // 'filemenu' is the menu that will be embedded inside the 'menubar'.
  wxMenu    *filemenu;
  // Canvas is the middle class between the interface and the OpenGL
  // canvas.
  Canvas    *canvas;
};
};
