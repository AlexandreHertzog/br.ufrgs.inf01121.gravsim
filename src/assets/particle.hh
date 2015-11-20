#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <vector>
#include <functional>

#include "point.hh"
#include "util.hh"

namespace GravSim {
namespace Assets {

const std::function<double(double, double, double, std::vector<double>, std::vector<double>)> FORCE =
  [] (double constant, double v1, double v2, std::vector<double> p1, std::vector<double> p2) {
    return constant * v1 * v2 / GravSim::Util::Square(GravSim::Util::DistanceBetween<double>(p1, p2));
  };

class Particle : public GravSim::Gui::Point {
public:
  Particle(
    const std::vector<double> position, const size_t size,
    const std::vector<double> velocity
  );
  ~Particle(void);

  std::vector<double> GetVelocity(void);

  virtual void ApplyForce(std::vector<double> force) = 0;
  virtual double GetValue(void) const = 0;
  virtual std::function<double(double, std::vector<double>)> GetField(void) const = 0;

protected:
  std::vector<double> _velocity;
};

} // namespace Assets
} // namespace GravSim

#endif
