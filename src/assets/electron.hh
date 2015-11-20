#ifndef _ELECTRON_H_
#define _ELECTRON_H_

#include "particle.hh"

namespace GravSim {
namespace Assets {

const double ECONSTANT = 8.9875517873681764e9;

class Electron : public Particle {
public:
  Electron(
      const std::vector<double> position, const size_t size,
      const std::vector<double> velocity, const double charge
    );
    
    double GetValue(void) const;
    std::function<double(double, std::vector<double>)> GetField(void) const;
  private:
    const double _charge;
  }; // class Electron

  } // namespace Assets
  } // namespace GravSim

#endif
