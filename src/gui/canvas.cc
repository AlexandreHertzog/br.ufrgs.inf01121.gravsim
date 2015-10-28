#include "canvas.hh"

#include <algorithm>

#ifdef __WXMAC__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "cmake_defines.hh"

using namespace GravSim::Gui;

BEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
  EVT_PAINT      (Canvas::OnRender)
END_EVENT_TABLE()

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

Canvas::Canvas(wxFrame *parent)
  : wxGLCanvas(
    parent, wxID_ANY, NULL, wxDefaultPosition, wxDefaultSize, 0, wxT(
      "Canvas"
    ))
{
  int argc = 1;
  char *argv[1] = {wxString((wxTheApp->argv)[0]).char_str()};
  glutInit(&argc, argv);
  
  _glcontext = new wxGLContext(this);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  
  // If we are in auto create points mode, create some points here.
  #ifdef _TEST_RENDER_
  for (int i = 0; i < 50; i++) {
    Point * point = new Point(2 * i, i, 10);
    AddPoint(point);
  }
  #endif
}

Canvas::~Canvas(void) {
  delete _glcontext;
  #ifdef _AUTONEWPARTS_
  for(auto point : _points) {
    delete point;
  }
  #endif
}

void Canvas::AddPoint(Point *point) {
  _points.push_back(point);
}

void Canvas::OnRender(wxPaintEvent &WXUNUSED(event)) {
  if (!IsShown()) {
    return;
  }
  
  wxGLCanvas::SetCurrent(*_glcontext);
  wxPaintDC(this);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  PrepareViewport(GetSize().x, GetSize().y);
  glLoadIdentity();
  
  for (auto point : _points) {
    point->Draw();
  }
  
  glFlush();
  SwapBuffers();
}

void Canvas::PrepareViewport(int width, int height) {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  gluOrtho2D(0, width, height, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

