// Copied from https://wiki.wxwidgets.org/WxGLCanvas

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <vector>

#include "point.hh"

namespace GravSim {
namespace Gui {
class Canvas : public wxGLCanvas {
public:
  Canvas(wxFrame *parent);
  ~Canvas(void);
  
  // This function does nothing if we are in _AUTONEWPARTS_ mode.
  void AddPoint(Point *point);
  
private:
  DECLARE_EVENT_TABLE()
  void OnRender(wxPaintEvent &event);
  void PrepareViewport(int width, int height);
  
  // Private variables.
  wxGLContext *_glcontext;
  std::vector<Point *> _points;
}; // class Canvas
}; // namespace Gui
}; // namespace GravSim
