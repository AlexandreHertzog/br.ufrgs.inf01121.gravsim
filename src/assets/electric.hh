#include "particle.hh"

namespace GravSim {
namespace Assets {
class Electric : public Particle {
public:
  Electric(double charge);
  ~Electric(void);
  
  double GetCharge(void);
private:
  double _charge;
}; // class ChargeParticle
}; // namespace Assets
}; // namespace GravSim
