#ifndef _BASE_H_
#define _BASE_H_

#include <exception>
#include <string>

#include "../engine/gsobject.hh"
#include "../engine/logger.hh"

namespace GravSim {
namespace Exception {

struct Base : public std::exception {
  Base(const GravSim::Engine::GSObject &who, const std::string &how) : who(who), how(how) {}
  virtual const char * what(void) const throw() = 0;

  const GravSim::Engine::GSObject &who;
  const std::string how;
};

} // namespace Exception
} // namespace GravSim

#endif
