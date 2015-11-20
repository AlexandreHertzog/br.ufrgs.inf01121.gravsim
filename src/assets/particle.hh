#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <vector>
#include <functional>

#include "point.hh"
#include "util.hh"

namespace GravSim {
namespace Assets {

class Particle : public GravSim::Gui::Point {
public:
  Particle(
    const std::vector<double> position, const size_t size,
    const std::vector<double> velocity
  );
  ~Particle(void);

  std::vector<double> GetVelocity(void);
  void SetVelocity(const std::vector<double> velocity);

  virtual void ApplyForce(std::vector<double> force) = 0;
  virtual double GetValue(void) const = 0;
  virtual std::function<double(double, std::vector<double>)> GetField(void) const = 0;

protected:
  std::vector<double> _velocity;
};

} // namespace Assets
} // namespace GravSim

#endif
