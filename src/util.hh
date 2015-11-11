#include <functional>
namespace GravSim {
namespace Util {
template <class A>
void ApplyToAll(A vec, std::function<void(size_t)> operation) {
	for (size_t i = 0; i < vec.size(); i++) {
		operation(i);
	}
}
} // namespace Util
} // namespace GravSim
