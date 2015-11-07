#include "storage.hh"

#include <random> // Used in the constructor.
#include <sstream> // Used to parse the strings from file.
#include <fstream> // File management.
#include <iostream>

using namespace GravSim::Engine;
using namespace GravSim::Gui;

Storage::Storage(const std::string filename, const int num_points) {
  _filename = filename;
}

Storage::~Storage(void) {
}

std::shared_ptr<Point> Storage::GetPoint(const size_t index) const {
  if (index >= _points.size()) {
    return NULL;
  }
  return _points[index];
}

void Storage::AppendPoint(std::shared_ptr<Point> point) {
  _points.push_back(point);
}

size_t Storage::SavePointsToFile(const std::string filename) {
  if (filename != "") {
    _filename = filename;
   }
  size_t count = 0;
  std::ofstream outfile(_filename);
  for (auto p : _points) {
    outfile << p->GetX() << " ";
    outfile << p->GetY() << " ";
    outfile << p->GetSize() << " ";
    outfile << std::endl;
    count++;
  }
  std::cout << "Storage::SavePointsToFile : Saved " << count <<
    " points to file." << std::endl;
  outfile.close();
  return count;
}

size_t Storage::LoadPointsFromFile(const std::string filename) {
  if (filename != "") {
    _filename = filename;
   }
  std::ifstream infile(_filename);
  // First, check if file exists.
  if (!infile.good()) {
    infile.close();
    return 0;
  }

  // Then, check if it is empty.
  infile.seekg(0, std::ios::end);
  size_t len = infile.tellg();
  if (len == 0) {
    infile.close();
    return 0;
  }
  infile.seekg(0);

  _points.clear();

  size_t count = 0;
  double buffer[10];
  std::string line;
  while (std::getline(infile, line)) {
    if (ReadDoubles(line, buffer) == 0) {
      break;
    }
    std::shared_ptr<Point> p(new Point(buffer[0], buffer[1], buffer[2]));
    AppendPoint(p);
    count++;
  }
  std::cout << "Storage::LoadPointsFromFile : Loaded " << count <<
    " points from file." << std::endl;
  infile.close();
  return count;
}

void Storage::GenerateRandom(const size_t num_points) {
  std::cout << "Storage::GenerateRandom : Generating new points." << std::endl;
  _points.clear();
  std::random_device dev;
  std::default_random_engine gen(dev());
  std::uniform_real_distribution<double> distr(0.0, 200.0);

  for (int i = 0; i < num_points; i++) {
    std::shared_ptr<Point> point(new Point(distr(gen), distr(gen), 10));
    AppendPoint(point);
  }
}

std::string Storage::GetFilename(void) const {
  return _filename;
}

size_t Storage::ReadDoubles(const std::string line, double *out) {
  const std::string delimitator = " ";

  size_t count = 0;

  size_t start = 0;
  auto end = line.find(delimitator);
  while (end != std::string::npos) {
    std::string strvalue = line.substr(start, end - start);
    out[count] = double(std::atof(strvalue.c_str()));

    // Update the indices.
    start = end + delimitator.length();
    end = line.find(delimitator, start);

    count++;
  }
  return count;
}
