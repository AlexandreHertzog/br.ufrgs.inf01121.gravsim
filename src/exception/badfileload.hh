#include <exception>
#include <string>

namespace GravSim {
namespace Exception {

struct BadFileLoad : public std::exception {
  BadFileLoad(const std::string filename) {
    this->filename = filename;
  }
  const char * what() const throw () {
    return "Bad file load.";
  }

  std::string filename;
};

} // namespace Exceptions
} // namespace GravSim
