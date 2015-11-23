#ifndef _POINT_H_
#define _POINT_H_

#include <cstddef>
#include <vector>

namespace GravSim {
namespace Gui {
class Point {
public:
  Point(const std::vector<double> position, const size_t size, const std::vector<float> color);
  void Draw(void);
  
  void LoadPosition(double &outx, double &outy) const;
  const std::vector<double> GetPosition(void) const;
  double GetX(void) const;
  double GetY(void) const;
  size_t GetSize(void) const;

protected:
  void SetPosition(const double x, const double y);
  void SetPosition(const std::vector<double> position);
  void IncrementPosition(const double x, const double y);
  void IncrementPosition(const std::vector<double> position);
private:
  std::vector<double> _position;
  size_t _size;
  const std::vector<float> _color;
  
}; // class Point
}; // namespace Gui
}; // namespace GravSim

#endif

