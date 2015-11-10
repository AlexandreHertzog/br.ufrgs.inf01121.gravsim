#include <vector>

#include "point.hh"

using std::vector;

namespace GravSim {
namespace Assets {
class Gravitron {
public:
  Gravitron(const double mass, const vector<double> velocity);
  ~Gravitron(void);

  double GetMass(void);

private:
  double _mass;
  vector<double> _velocity;
}; // class Gravitron
}; // namespace GravSim
}; // namespace Assets
