#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <vector>
#include <memory>
#include <fstream>
#include <string>

#include "logger.hh"

#include "point.hh"
#include "particle.hh"
#include "gsobject.hh"

// Exceptions
#include "badindex.hh"
#include "badfileload.hh"
#include "badnewfile.hh"

namespace GravSim {
namespace Engine {
class Storage : public GSObject {
public:
  Storage(const std::string filename = "default.gsim", const int num_particles = 50);
  ~Storage(void);

  std::shared_ptr<GravSim::Assets::Particle> GetParticle(const size_t index) const 
    throw(GravSim::Exception::BadIndex);
  std::shared_ptr<GravSim::Gui::Point> GetPoint(const size_t index) const
    throw(GravSim::Exception::BadIndex);
  void AppendParticle(std::shared_ptr<GravSim::Assets::Particle> particle);
  const size_t GetNumParticles(void) const;
  void ClearParticles(void);

  size_t SaveParticlesToFile(const std::string filename = "");

  size_t LoadParticlesFromFile(const std::string filename = "") throw(GravSim::Exception::BadFileLoad);
  void GenerateRandom(const size_t num_particles, int p_type) throw(GravSim::Exception::BadNewFile);

  std::string GetFilename(void) const;

  // Parent functions
  const std::string GetObjName(void) const;

private:
  std::vector<std::shared_ptr<GravSim::Assets::Particle>> _particles;
  size_t _iterator;
  std::string _filename;

  std::vector<double> ReadDoubles(const std::string line);
}; // class Storage
}; // namespace Engine
}; // namespace GravSim

#endif
