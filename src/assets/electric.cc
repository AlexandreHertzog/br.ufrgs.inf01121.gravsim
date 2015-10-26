#include "electric.hh"

using namespace GravSim::Assets;

Electric::Electric(double charge) {
  _charge = charge;
}

Electric::~Electric(void) {
}

double Electric::GetCharge(void) {
  return _charge;
}
