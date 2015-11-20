#include "gravitron.hh"

namespace GravSim {
namespace Assets {

class Electron {
public:
  Electron(const double charge);
  ~Electron(void);
  
  const double GetCharge(void) const;
private:
  double _charge;
}; // class ChargeParticle

} // namespace Assets
} // namespace GravSim
