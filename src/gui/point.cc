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

using namespace GravSim::Gui;
// TODO: change all constants after the NUM_DIMENTIONS constant changes place.

Point::Point(const double x, const double y, const size_t size) {
  SetPosition(x, y);
  _size = size;
}

Point::Point(const vector<double> position, const size_t size) {
  SetPosition(position);
  _size = size;
}

Point::~Point(void) {
}

void Point::Draw(void) {
  glPointSize(_size);
  glBegin(GL_POINTS);
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

double Point::SquareOfDistance(const std::vector<double> point) {
  // Square of first term...
  double distx = (_position[0] - point[0]);
  distx *= distx;
  // Square of second term
  double disty = (_position[1] - point[1]);
  disty *= disty;
  return distx + disty;
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
