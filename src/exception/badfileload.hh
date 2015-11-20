#include "base.hh"

namespace GravSim {
namespace Exception {

struct BadFileLoad : public Base {
  BadFileLoad(const GravSim::Engine::GSObject &who, const std::string &how) : Base(who, how) {
    GravSim::Engine::Logger::LogError(*this, what(), how);
  }
  const char * what() const throw () {
    return "Bad file load.";
  }
};

} // namespace Exceptions
} // namespace GravSim
