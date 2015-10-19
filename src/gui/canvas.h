// Copied from https://wiki.wxwidgets.org/WxGLCanvas

#include <wx/wx.h>
#include <wx/glcanvas.h>

#ifdef __WXMAC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef WIN32
#include <unistd.h>
#endif

namespace GravSimGui {
class Canvas : public wxGLCanvas {
public:
  Canvas(wxFrame *parent);
  ~Canvas(void);
  void Paintit(wxPaintEvent &event);
  
private:
  DECLARE_EVENT_TABLE()
  void Render(void);
  wxGLContext *glcontext;
};
};
