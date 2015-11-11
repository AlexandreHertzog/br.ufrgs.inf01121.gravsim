#include <functional>

#include "exceptions/zerodivision.hh"

namespace GravSim {
namespace Util {
template <class A>
inline void ApplyToAll(A vec, std::function<void(size_t)> operation) {
	for (size_t i = 0; i < vec.size(); i++) {
		operation(i);
	}
}

template <typename Operator>
inline Operator Division(Operator num, Operator den) {
	if (den == 0) {
		throw GravSim::Exceptions::ZeroDivision();
	}
	return num / den;
}
} // namespace Util
} // namespace GravSim
