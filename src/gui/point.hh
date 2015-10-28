#include <cstddef>

namespace GravSim {
namespace Gui {
class Point {
public:
  Point(const double *position, const size_t size = 0);
  Point(const double x = 0, const double y = 0, const size_t size = 0);
  void Draw(void);
  
  void SetPosition(const double x, const double y);
  void SetPosition(const double *position);
  void LoadPosition(double &outx, double &outy);
  void LoadPosition(double *out);

protected:
  void IncrementPosition(const double x, const double y);
  void IncrementPosition(const double *position);

private:
  double _position[2];
  size_t _size;

}; // class Point
}; // namespace Gui
}; // namespace GravSim
