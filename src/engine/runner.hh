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
	Runner(shared_ptr<GravSim::Engine::Storage> storage, const wxString &title);
	~Runner(void);

	void Execute(void);
	const std::string GetObjName(void) const;

protected:
	// Functions from Window.
	void SavePointsToFile(const std::string filename = "");
	void LoadPointsFromFile(const std::string filename = "");
	void GenerateRandom(const size_t numparticles);
	const std::string GetFilename(void);

private:
	shared_ptr<GravSim::Engine::Storage> _storage;
}; // class Runner
} // namespace Engine
} // namespace GravSim

#endif