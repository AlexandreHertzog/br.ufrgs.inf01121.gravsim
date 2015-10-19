#include "canvas.h"

BEGIN_EVENT_TABLE(GravSimGui::Canvas, wxGLCanvas)
  EVT_PAINT      (GravSimGui::Canvas::Paintit)
END_EVENT_TABLE()

GravSimGui::Canvas::Canvas(wxFrame *parent)
  : wxGLCanvas(
    parent, wxID_ANY, NULL, wxDefaultPosition, wxDefaultSize, 0, wxT(
      "Canvas"
    ))
{
  int argc = 1;
  char *argv[1] = {wxString((wxTheApp->argv)[0]).char_str()};
  glutInit(&argc, argv);
  
  glcontext = new wxGLContext(this);
}

GravSimGui::Canvas::~Canvas(void) {
  delete glcontext;
}

void GravSimGui::Canvas::Paintit(wxPaintEvent &WXUNUSED(event)) {
  Render();
}

void GravSimGui::Canvas::Render(void) {
  // Initialize the rendering parameters.
  wxGLCanvas::SetCurrent(*glcontext);
  wxPaintDC(this);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
  
  // Here the renders will be made.
  
  // Post-render operations.
  glFlush();
  SwapBuffers();
}
