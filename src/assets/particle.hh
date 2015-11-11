#include <vector>

#include "gravitron.hh"
#include "electron.hh"
#include "point.hh"

using std::vector;

namespace GravSim {
namespace Assets {

using GravSim::Gui::Point;
class Particle : public Gravitron, Electron {
public:
  // All terms constructor.
  Particle(
    // Point components.
    const vector<double> position, const size_t size,
    // Gravitron components.
    const double mass, const vector<double> velocity,
    // Electron components.
    const double charge
  );
  // Gravitron terms constructor.
  Particle(
    const vector<double> position, const size_t size,
    const double mass, const vector<double> velocity
  );
  // Electron terms constructor
  Particle(
    const vector<double> position, const size_t size,
    const double charge
  );
  ~Particle(void);
};

} // namespace Assets
} // namespace GravSim
