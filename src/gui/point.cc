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

Point::Point(const double *position, const size_t size) {
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

void Point::LoadPosition(double *out) const {
  std::copy(_position, _position + 2, out);
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

void Point::SetPosition(const double *position) {
  std::copy(position, position + 2, _position);
}

void Point::IncrementPosition(const double x, const double y) {
  _position[0] += x;
  _position[1] += y;
}

void Point::IncrementPosition(const double *position) {
  _position[0] += position[0];
  _position[1] += position[1];
}