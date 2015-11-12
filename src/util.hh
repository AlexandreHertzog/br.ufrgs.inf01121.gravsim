#include <functional>
#include <cmath>

namespace GravSim {
namespace Util {

template <class A>
inline void ApplyToAll(A vec, std::function<void(size_t)> operation) {
  for (size_t i = 0; i < vec.size(); i++) {
    operation(i);
  }
}

template <typename A>
inline A NormaliseVector(A vec) {
  double sumofparts = 0;
  ApplyToAll(vec, [&sumofparts, vec] (size_t i) {sumofparts += pow(vec[i], 2);});
  double magnitude = sqrt(sumofparts);
  ApplyToAll(vec, [&vec, magnitude] (size_t i) {vec[i] /= magnitude;});
  return vec;
}

} // namespace Util
} // namespace GravSim
