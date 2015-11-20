#include <vector>

#include "gravitron.hh"
#include "electron.hh"
#include "point.hh"

namespace GravSim {
namespace Assets {

class Particle : public Gravitron, Electron {
public:
  // All terms constructor.
  Particle(
    // Point components.
    const std::vector<double> position, const size_t size,
    // Gravitron components.
    const double mass, const std::vector<double> velocity,
    // Electron components.
    const double charge
  );
  // Gravitron terms constructor.
  Particle(
    const std::vector<double> position, const size_t size,
    const double mass, const std::vector<double> velocity
  );
  // Electron terms constructor
  Particle(
    const std::vector<double> position, const size_t size,
    const double charge
  );
  ~Particle(void);
};

} // namespace Assets
} // namespace GravSim
