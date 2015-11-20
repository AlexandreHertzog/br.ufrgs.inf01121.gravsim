#ifndef _BADINDEX_H_
#define _BADINDEX_H_

#include "base.hh"

namespace GravSim {
namespace Exception {

struct BadIndex : public Base {
  BadIndex(const GravSim::Engine::GSObject &who, const std::string &how) : Base(who, how) {
    GravSim::Engine::Logger::LogError(*this, what(), how);
  }

  const char * what() const throw() {
    return "Bad index.";
  }
};

} // namespace Exceptions
} // namespace GravSim

#endif
