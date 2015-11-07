#ifndef _POINT_H_
#define _POINT_H_

#include <cstddef>

namespace GravSim {
namespace Gui {
class Point {
public:
  Point(const double *position, const size_t size = 0);
  Point(const double x = 0, const double y = 0, const size_t size = 0);
  ~Point(void);
  void Draw(void);
  
  void LoadPosition(double &outx, double &outy) const;
  void LoadPosition(double *out) const;
  double GetX(void) const;
  double GetY(void) const;
  size_t GetSize(void) const;

protected:
  void SetPosition(const double x, const double y);
  void SetPosition(const double *position);
  void IncrementPosition(const double x, const double y);
  void IncrementPosition(const double *position);

private:
  double _position[2];
  size_t _size;

}; // class Point
}; // namespace Gui
}; // namespace GravSim

#endif

