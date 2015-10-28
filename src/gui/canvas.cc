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

#ifndef WIN32
#include <unistd.h>
#endif

#include "cmake_defines.hh"

using namespace GravSim::Gui;

BEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
  EVT_PAINT      (Canvas::OnRender)
END_EVENT_TABLE()

/* Unfortunately, this is necessary. g++ points out many warning about internal
 * wxGLCanvas functions that are never used in our program, which causes a lot
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
  
  // If we are in auto create particles mode, create some particles here.
  #ifdef _AUTONEWPARTS_
  double position[GravSim::Assets::NUM_DIMENSIONS];
  double velocity[GravSim::Assets::NUM_DIMENSIONS];
  velocity[0] = 0.0;
  velocity[1] = 0.0;
  for (int i = 0; i < 50; i++) {
    position[0] = double(2 * i);
    position[1] = double(i);
    GravSim::Assets::Particle * particle = new GravSim::Assets::Particle(
      0.0, velocity, position
    );
    _particles.push_back(particle);
  }
  #endif
}

Canvas::~Canvas(void) {
  delete _glcontext;
  #ifdef _AUTONEWPARTS_
  for(auto particle : _particles) {
    delete particle;
  }
  #endif
}

void Canvas::AddParticle(GravSim::Assets::Particle *particle) {
  #ifndef _AUTONEWPARTS_
  _particles.push_back(particle);
  #else
  std::cout << "GravSim::Gui::Canvas::AddParticle : Not adding new particle "
    "since we are in auto create particle mode." << std::endl;
  #endif
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
  
  // A single area in memory will be reused for all points.
  double current_point[GravSim::Assets::NUM_DIMENSIONS];
  
  // TODO: get this as an attribute from the particle.
  glPointSize(10);
  
  glBegin(GL_POINTS);
  for (auto particle : _particles) {
    particle->LoadPos(current_point);
    glVertex3f(current_point[0]*10, current_point[1]*10, 0);
  }
  glEnd();
  
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

