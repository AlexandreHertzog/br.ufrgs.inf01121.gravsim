#ifndef _RUNNER_H_
#define _RUNNER_H_

#include <memory>
#include <string>
#include <thread>

#include "window.hh"
#include "storage.hh"
#include "gsobject.hh"

namespace GravSim {
namespace Engine {

// TODO: parametrize this.
const long SPEEDFACTOR = 1;
const double UPDATEFREQ = 1000/60;

class Runner : public GravSim::Gui::Window, public GSObject {
public:
  Runner(const wxString &title);
  ~Runner(void);

  // Simulation phases
  enum class Phase {
    RUNNING, PAUSED, STEPPED
  };

  void Execute(void);
  const std::string GetObjName(void) const;

protected:
  // Functions from Window.
  void SaveParticlesToFile(const std::string filename = "");
  void LoadParticlesFromFile(const std::string filename = "");
  void GenerateRandom(const size_t numparticles);
  const std::string GetFilename(void);
  void AddParticle(const std::vector<double> params);

  void OnPause(wxCommandEvent &event);
  void OnResume(wxCommandEvent &event);
  void OnStop(wxCommandEvent &event);
  void OnStep(wxCommandEvent &event);

private:
  void StepSimulation(void);
  void StopThread(void);
  void StartThread(void);

  std::shared_ptr<GravSim::Engine::Storage> _storage;

  // Thread related stuff.
  std::unique_ptr<std::thread> _exec;
  bool _isrunning;

  // Results and helper functions.
  std::vector<double> **_resultmatrix;
  int _partcount;
  void InitResults(void);

  Phase _simphase;
}; // class Runner
} // namespace Engine
} // namespace GravSim

#endif
