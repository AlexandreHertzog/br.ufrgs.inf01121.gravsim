#include "storage.hh"

#include <random>

using namespace GravSim::Engine;
using namespace GravSim::Gui;

Storage::Storage(const int num_points) {
  std::default_random_engine gen;
  std::uniform_real_distribution<double> distr(0.0, 200.0);

  for (int i = 0; i < num_points; i++) {
    std::shared_ptr<Point> point(new Point(distr(gen), distr(gen), 10));
    AppendPoint(point);
  }
}

Storage::Storage(std::vector<std::shared_ptr<Point>> points) {
  // TODO: Implement this.
}

std::shared_ptr<Point> Storage::GetPoint(const size_t index) const {
  if (index > _points.size()) {
    return NULL;
  }
  return _points[index];
}

void Storage::AppendPoint(std::shared_ptr<Point> point) {
  _points.push_back(point);
}
