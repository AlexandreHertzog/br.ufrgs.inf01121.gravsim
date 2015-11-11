#ifndef _GRAVITRON_H_
#define _GRAVITRON_H_

#include <vector>
#include <functional>

#include "point.hh"

using std::vector;

namespace GravSim {
namespace Assets {

const double GRAVCONSTANT = 6.674e-11;

class Gravitron : public GravSim::Gui::Point {
public:
  Gravitron(const double mass, const vector<double> velocity);
  ~Gravitron(void);

  double GetMass(void);

  // Force = (gravity constant) * (_mass * mass) / (distance * distance)
  /* OK, so some modification has to be done here for this to work nicely.
   * First, we most likely won't have a distance. Since we also need the positions
   * of both particles to calculate the force vector, we can modifify the distance
   * to facilitate our lives:
   * distance² = catet1² + catet2²
   * cateti² = distance(point1, point2)
   * cateti² = (point1.x - point2.x)² + (point1.y - point2.y)² */
  std::function<double(double)> GetGravField(const vector<double> point);

  void ApplyForce(const vector<double> force);

private:
  // Here is hoping that this static won't blow up on the future. It is necessary for the lambda function.
  static double _mass;
  vector<double> _velocity;
}; // class Gravitron
}; // namespace GravSim
}; // namespace Assets

#endif
