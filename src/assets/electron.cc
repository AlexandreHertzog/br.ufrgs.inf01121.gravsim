#include "electron.hh"

using namespace GravSim::Assets;

Electron::Electron(const double charge) {
  _charge = charge;
}

Electron::~Electron(void) {
}

const double Electron::GetCharge(void) const {
  return _charge;
}
