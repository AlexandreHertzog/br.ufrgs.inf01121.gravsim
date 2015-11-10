#ifndef _POINT_H_
#define _POINT_H_

#include <cstddef>
#include <vector>

using std::vector;

namespace GravSim {
namespace Gui {
class Point {
public:
  Point(const vector<double> position, const size_t size = 0);
  Point(const double x = 0, const double y = 0, const size_t size = 0);
  ~Point(void);
  void Draw(void);
  
  void LoadPosition(double &outx, double &outy) const;
  const vector<double> GetPosition(void) const;
  double GetX(void) const;
  double GetY(void) const;
  size_t GetSize(void) const;

protected:
  void SetPosition(const double x, const double y);
  void SetPosition(const vector<double> position);
  void IncrementPosition(const double x, const double y);
  void IncrementPosition(const vector<double> position);

private:
  vector<double> _position;
  size_t _size;

}; // class Point
}; // namespace Gui
}; // namespace GravSim

#endif

