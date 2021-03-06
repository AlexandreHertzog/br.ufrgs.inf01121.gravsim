#include "point.hh"

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

using std::vector;

using namespace GravSim::Gui;
// TODO: change all constants after the NUM_DIMENTIONS constant changes place.
// testing: separated float values for r g b 
Point::Point(const vector<double> pos, const size_t size, const vector<float> color)
  : _color(color)
{
  SetPosition(pos);
  _size = size;
}

void Point::Draw(void) {
  glPointSize(_size);
  glBegin(GL_POINTS);
    glColor3f(_color[0], _color[1], _color[2]);
    glVertex3f(_position[0], _position[1], 0);
  glEnd();
}

void Point::LoadPosition(double &outx, double &outy) const {
  outx = _position[0];
  outy = _position[1];
}

const vector<double> Point::GetPosition(void) const {
  return _position;
}

double Point::GetX(void) const {
  return _position[0];
}

double Point::GetY(void) const {
  return _position[1];
}

size_t Point::GetSize(void) const {
  return _size;
}

void Point::SetPosition(const double x, const double y) {
  _position[0] = x;
  _position[1] = y;
}

void Point::SetPosition(const vector<double> position) {
  _position = position;
}

void Point::IncrementPosition(const double x, const double y) {
  _position[0] += x;
  _position[1] += y;
}

void Point::IncrementPosition(const vector<double> position) {
  if (position.size() != _position.size()) {
    return;
  }
  for(size_t i = 0; i < _position.size(); i++) {
    _position[i] += position[i];
  }
}
