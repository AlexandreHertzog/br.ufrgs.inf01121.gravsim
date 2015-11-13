#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <vector>
#include <memory>

#include "point.hh"
#include "storage.hh"

namespace GravSim {
namespace Gui {
class Canvas : public wxGLCanvas {
public:
  Canvas(std::shared_ptr<GravSim::Engine::Storage> storage, wxFrame *parent);
  ~Canvas(void);
  
private:
  DECLARE_EVENT_TABLE()
  void OnRender(wxPaintEvent &event);
  void PrepareViewport(int width, int height);
  
  // Private variables.
  wxGLContext *_glcontext;
  std::shared_ptr<GravSim::Engine::Storage> _storage;
}; // class Canvas
}; // namespace Gui
}; // namespace GravSim

#endif
