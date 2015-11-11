#include "storage.hh"

#include <random> // Used in the constructor.
#include <sstream> // Used to parse the strings from file.
#include <fstream> // File management.

#include "logger.hh"

using namespace GravSim::Engine;
using namespace GravSim::Gui;
using GravSim::Gui::Point;
using GravSim::Assets::Particle;
using std::vector;

Storage::Storage(const std::string filename, const int num_particles) 
	: GSObject()
{
  _filename = filename;
}

Storage::~Storage(void) {
}

std::shared_ptr<Particle> Storage::GetParticle(const size_t index) const {
  if (index >= _particles.size()) {
    return NULL;
  }
  return _particles[index];
}

std::shared_ptr<Point> Storage::GetPoint(const size_t index) const {
  if (index >= _particles.size()) {
    return NULL;
  }
  return _particles[index];
}

void Storage::AppendParticle(std::shared_ptr<Particle> point) {
  _particles.push_back(point);
}

size_t Storage::SaveParticlesToFile(const std::string filename) {
  if (filename != "") {
    _filename = filename;
   }
  size_t count = 0;
  std::ofstream outfile(_filename);
  for (auto p : _particles) {
    outfile << p->GetX() << " ";
    outfile << p->GetY() << " ";
    outfile << p->GetSize() << " ";
    outfile << std::endl;
    count++;
  }
  Logger::LogInfo(*this, "Saved points to file.");
  outfile.close();
  return count;
}

size_t Storage::LoadParticlesFromFile(const std::string filename) {
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

  _particles.clear();

  // To avoid continuous loop allocations.
  vector<double> fromfile, position, velocity;
  std::string line;
  while (std::getline(infile, line)) {
    fromfile = ReadDoubles(line);
    if (fromfile.size() == 0) {
      break;
    }
    position = {fromfile[0], fromfile[1]};
    velocity = {fromfile[4], fromfile[5]};
    std::shared_ptr<Particle> p(
      new Particle(position, fromfile[2], fromfile[3], velocity, fromfile[6])
    );
    AppendParticle(p);
  }
  Logger::LogInfo(*this, "Loaded points from file.");
  infile.close();
  return _particles.size();
}

void Storage::GenerateRandom(const size_t num_particles) {
  Logger::LogInfo(*this, "Generating new points.");
  _particles.clear();
  std::random_device dev;
  std::default_random_engine gen(dev());
  std::uniform_real_distribution<double> position_random(0.0, 200.0);
  std::uniform_real_distribution<double> vector_random(0.0, 200.0);
  std::uniform_real_distribution<double> mass_random(1.0, 200.0);
  std::uniform_int_distribution<int> scalar_random(1, 20);

  vector<double> position, velocity;
  double mass;
  size_t size;

  for (int i = 0; i < num_particles; i++) {
    position = {position_random(gen), position_random(gen)};
    velocity = {vector_random(gen), vector_random(gen)};
    mass = mass_random(gen);
    size = mass / 10;
    std::shared_ptr<Particle> point(
      new Particle(position, size, mass, velocity, vector_random(gen))
    );
    AppendParticle(point);
  }
}

std::string Storage::GetFilename(void) const {
  return _filename;
}

const std::string Storage::GetObjName(void) const {
	return "GravSim::Engine::Storage";
}

vector<double> Storage::ReadDoubles(const std::string line) {
  vector<double> out;
  const std::string delimitator = " ";

  size_t start = 0;
  auto end = line.find(delimitator);
  while (end != std::string::npos) {
    std::string strvalue = line.substr(start, end - start);
    out.push_back(double(std::atof(strvalue.c_str())));

    // Update the indices.
    start = end + delimitator.length();
    end = line.find(delimitator, start);
  }
  return out;
}
