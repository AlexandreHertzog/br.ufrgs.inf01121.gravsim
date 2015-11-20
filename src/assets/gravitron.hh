#ifndef _GRAVITRON_H_
#define _GRAVITRON_H_

#include <vector>
#include <functional>

#include "particle.hh"
#include "util.hh"

namespace GravSim {
namespace Assets {

const double GRAVCONSTANT = 6.674e-11;
const std::function<double(double, double, std::vector<double>, std::vector<double>)> GFORCE =
  [] (double m1, double m2, std::vector<double> p1, std::vector<double> p2) {
    return GRAVCONSTANT * m1 * m2 / GravSim::Util::Square(GravSim::Util::DistanceBetween<double>(p1, p2));
  };


class Gravitron : public Particle {
public:
  Gravitron(
    const std::vector<double> position, const double size,
    const std::vector<double> velocity, const double mass
  );
  ~Gravitron(void);

  double GetValue(void) const;

  // Force = (gravity constant) * (_mass * mass) / (distance * distance)
  /* OK, so some modification has to be done here for this to work nicely.
   * First, we most likely won't have a distance. Since we also need the positions
   * of both particles to calculate the force vector, we can modifify the distance
   * to facilitate our lives:
   * distance² = catet1² + catet2²
   * cateti² = distance(point1, point2)
   * cateti² = (point1.x - point2.x)² + (point1.y - point2.y)² */
  //std::function<double(double)> GetGravField(const vector<double> point);
  // This returns the grav function without some stuff: it requires (as parameters)
  // the mass of the second object and the point in space of that parameter.
  std::function<double(double, std::vector<double>)> GetField(void) const;


  void ApplyForce(const std::vector<double> force);

private:
  double _mass;
}; // class Gravitron
}; // namespace GravSim
}; // namespace Assets

#endif
