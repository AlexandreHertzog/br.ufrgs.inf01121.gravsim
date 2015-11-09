#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <vector>
#include <memory>
#include <fstream>
#include <string>

#include "point.hh"
#include "gsobject.hh"

namespace GravSim {
namespace Engine {
class Storage : public GSObject {
public:
  Storage(const std::string filename = "default.gsim", const int num_points = 50);
  ~Storage(void);

  std::shared_ptr<GravSim::Gui::Point> GetPoint(const size_t index) const;
  void AppendPoint(std::shared_ptr<GravSim::Gui::Point> point);

  size_t SavePointsToFile(const std::string filename = "");
  size_t LoadPointsFromFile(const std::string filename = "");
  void GenerateRandom(const size_t num_points);

  std::string GetFilename(void) const;

  // Parent functions
  const std::string GetObjName(void) const;

private:
  std::vector<std::shared_ptr<GravSim::Gui::Point>> _points;
  size_t _iterator;
  std::string _filename;

  size_t ReadDoubles(const std::string line, double *out);
}; // class Storage
}; // namespace Engine
}; // namespace GravSim

#endif
