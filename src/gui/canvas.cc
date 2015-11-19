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

#include "badindex.hh"


using namespace GravSim::Gui;
using GravSim::Exception::BadIndex;

BEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
  EVT_PAINT      (Canvas::OnRender)
END_EVENT_TABLE()

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// Just for testing purpose
// TODO(pedro): After finishing and testing the optmized way of coloring the particles
// get rid of this.
int aux = 0;
float p_mass = 0;
float r_number = 1;
float g_number = 1;
float b_number = 1;
//

Canvas::Canvas(
  std::shared_ptr<GravSim::Engine::Storage> storage, wxFrame *parent
)
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

  _storage = storage;
}

Canvas::~Canvas(void) {
  delete _glcontext;
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
  for (size_t i = 0; i < _storage->GetNumParticles(); i++) {
    try {
        if (aux == 0) {
            p_mass = _storage->GetParticle(i)->GetMass();
            r_number = ((float) rand() / (RAND_MAX));
            g_number = ((float) rand() / (RAND_MAX));
            b_number = ((float) rand() / (RAND_MAX));
            aux = 1;
        }
        _storage->GetPoint(i)->Draw(r_number, g_number, b_number);      
    } catch (const BadIndex badindex) {
        break;
    }
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
  
  // TODO: Maybe change these constant values in the future.
  gluOrtho2D(0, 200, 200, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

