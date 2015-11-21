#ifndef _UTIL_H_
#define _UTIL_H_

#include <functional>
#include <cmath>
#include <vector>

namespace GravSim {
namespace Util {

template <typename TNumber> 
TNumber Square(const TNumber num) {
  return num * num;
}

template <class TVector>
inline void ApplyToAll(TVector vec, std::function<void(size_t)> operation) {
  for (size_t i = 0; i < vec.size(); i++) {
    operation(i);
  }
}

template <typename TVector>
inline TVector NormaliseVector(TVector vec) {
  double sumofparts = 0;
  ApplyToAll(vec, [&sumofparts, vec] (size_t i) {sumofparts += Square(vec[i]);});
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
  TVector res;
  ApplyToAll(vec1, [&res, vec1, vec2] (size_t i) {res.push_back(vec1[i] + vec2[i]);});
  return res;
}

template <typename TNumber, class TVector>
TNumber DistanceBetween(const TVector v1, const TVector v2) {
  return sqrt(Square(v1[0] - v2[0]) + Square(v1[1] - v2[1]));
}

template <class TVector>
inline void ClearMatrix(TVector &vec, const int index, const int maxindex) {
  if (index >= maxindex) {
    return;
  }
  ClearMatrix(vec[index], index+1, maxindex);
  delete[] vec;
}

template <>
inline void ClearMatrix<std::vector<double>>(std::vector<double> &vec, const int index, const int maxindex) {
  vec.clear();
  return;
}

} // namespace Util
} // namespace GravSim

#endif
