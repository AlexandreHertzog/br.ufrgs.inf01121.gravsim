#include "particle.hh"

namespace GravSim {
namespace Assets {
class Electric : public Particle {
public:
  Electric(
    // Physical components
    const double charge, const double mass, const double *velocity,
    const double *position,
    // Render components
    const size_t size = 0
  );
  ~Electric(void);
  
  double GetCharge(void);
private:
  double _charge;
}; // class ChargeParticle
}; // namespace Assets
}; // namespace GravSim
