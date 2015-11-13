#include <exception>
#include <string>

#include "base.hh"

namespace GravSim {
namespace Exception {

struct BadNewFile : public Base {
  BadNewFile(const GravSim::Engine::GSObject &who, const std::string how)
    : Base(who, how) {}
  const char * what(void) const throw() {
    return "Bad new file.";
  }
};

} // namespace Exception
} // namespace GravSim
