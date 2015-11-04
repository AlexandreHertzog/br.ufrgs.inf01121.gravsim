// Copied from https://wiki.wxwidgets.org/WxGLCanvas

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <vector>

#include "point.hh"
#include "storage.hh"

namespace GravSim {
namespace Gui {
class Canvas : public wxGLCanvas {
public:
  Canvas(const GravSim::Engine::Storage *storage, wxFrame *parent);
  ~Canvas(void);
  
private:
  DECLARE_EVENT_TABLE()
  void OnRender(wxPaintEvent &event);
  void PrepareViewport(int width, int height);
  
  // Private variables.
  wxGLContext *_glcontext;
  const GravSim::Engine::Storage *_storage;
}; // class Canvas
}; // namespace Gui
}; // namespace GravSim
