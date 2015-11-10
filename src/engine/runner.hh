#ifndef _RUNNER_H_
#define _RUNNER_H_

#include <memory>
#include <string>

#include "window.hh"
#include "storage.hh"
#include "gsobject.hh"

namespace GravSim {
namespace Engine {

using std::shared_ptr;
using std::unique_ptr;

class Runner : public GravSim::Gui::Window, public GSObject {
public:
	Runner(unique_ptr<GravSim::Engine::Storage> storage, const wxString &title);
	~Runner(void);

	void Execute(void);
	const std::string GetObjName(void) const;

private:
}; // class Bootstraper
} // namespace Engine
} // namespace GravSim

#endif
