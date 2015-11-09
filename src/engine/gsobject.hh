#ifndef _GSOBJECT_H_
#define _GSOBJECT_H_
#include <string>

namespace GravSim {
namespace Engine {
class GSObject {
public:
	GSObject(void);
	~GSObject(void);

	virtual const std::string GetObjName(void) const = 0;
};
} // namespace Engine
} // namespace GravSim

#endif
