#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <vector>
#include <memory>

#include "point.hh"

namespace GravSim {
namespace Engine {
class Storage {
public:
  Storage(const int num_points = 50);
  Storage(std::vector<std::shared_ptr<GravSim::Gui::Point>> points);

  std::shared_ptr<GravSim::Gui::Point> GetPoint(const size_t index) const;
  void AppendPoint(std::shared_ptr<GravSim::Gui::Point> point);

private:
  std::vector<std::shared_ptr<GravSim::Gui::Point>> _points;
  size_t _iterator;
}; // class Storage
}; // namespace Engine
}; // namespace GravSim

#endif
