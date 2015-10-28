// Copied from https://wiki.wxwidgets.org/WxGLCanvas

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <vector>

#include "particle.hh"

namespace GravSim {
namespace Gui {
class Canvas : public wxGLCanvas {
public:
  Canvas(wxFrame *parent);
  ~Canvas(void);
  
  // This function does nothing if we are in _AUTONEWPARTS_ mode.
  void AddParticle(GravSim::Assets::Particle *particle);
  
private:
  DECLARE_EVENT_TABLE()
  void OnRender(wxPaintEvent &event);
  void PrepareViewport(int width, int height);
  
  // Private variables.
  wxGLContext *_glcontext;
  std::vector<GravSim::Assets::Particle *> _particles;
}; // class Canvas
}; // namespace Gui
}; // namespace GravSim
