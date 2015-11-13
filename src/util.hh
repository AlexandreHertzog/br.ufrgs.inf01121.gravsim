#include <functional>
#include <cmath>

namespace GravSim {
namespace Util {

template <class TVector>
inline void ApplyToAll(TVector vec, std::function<void(size_t)> operation) {
  for (size_t i = 0; i < vec.size(); i++) {
    operation(i);
  }
}

template <typename TVector>
inline TVector NormaliseVector(TVector vec) {
  double sumofparts = 0;
  ApplyToAll(vec, [&sumofparts, vec] (size_t i) {sumofparts += pow(vec[i], 2);});
  double magnitude = sqrt(sumofparts);
  ApplyToAll(vec, [&vec, magnitude] (size_t i) {vec[i] /= magnitude;});
  return vec;
}

template <class TVector, typename TNumber>
inline TVector NumTimesVec(const TNumber number, const TVector vec) {
  TVector res(vec.size());
  ApplyToAll(vec, [&res, number, vec] (size_t i) {res[i] = number * vec[i];});
  return res;
}

template <class TVector>
inline TVector VecPlusVec(const TVector vec1, const TVector vec2) {
  TVector res(vec1.size());
  ApplyToAll(vec1, [&res, vec1, vec2] (size_t i) {res[i] = vec1[i] + vec2[i];});
  return res;
}

} // namespace Util
} // namespace GravSim
