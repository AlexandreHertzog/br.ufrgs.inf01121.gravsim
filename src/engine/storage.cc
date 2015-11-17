#include "storage.hh"

#include <random> // Used in the constructor.
#include <sstream> // Used to parse the strings from file.
#include <fstream> // File management.


using namespace GravSim::Engine;
using GravSim::Exception::BadFileLoad;
using GravSim::Exception::BadNewFile;
using GravSim::Exception::BadIndex;
using GravSim::Gui::Point;
using GravSim::Assets::Particle;

using std::vector;
using std::shared_ptr;
using std::string;

Storage::Storage(const string filename, const int num_particles) 
	: GSObject()
{
  _filename = filename;
}

Storage::~Storage(void) {
}

shared_ptr<Particle> Storage::GetParticle(const size_t index) const throw(BadIndex) {
  shared_ptr<Particle> p;
  try {
    p = _particles[index];
  } catch (...) {
    string how = "Index = ";
    how += index;
    throw BadIndex(*this, how);
  }
  return p;
}

shared_ptr<Point> Storage::GetPoint(const size_t index) const throw(BadIndex) {
  return GetParticle(index);
}

void Storage::AppendParticle(shared_ptr<Particle> point) {
  _particles.push_back(point);
}

const size_t Storage::GetNumParticles(void) const {
  return _particles.size();
}

size_t Storage::SaveParticlesToFile(const string filename) {
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

size_t Storage::LoadParticlesFromFile(const string filename) throw(BadFileLoad) {
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
  string line;
  shared_ptr<Particle> p;
  while (std::getline(infile, line)) {
    fromfile = ReadDoubles(line);
    if (fromfile.size() == 0) {
      break;
    }
    position = {fromfile[0], fromfile[1]};
    velocity = {fromfile[4], fromfile[5]};
    try {
      p = shared_ptr<Particle>(new Particle(position, fromfile[2], fromfile[3], velocity, fromfile[6]));
    } catch (...) {
      throw BadFileLoad(filename);
    }
    AppendParticle(p);
  }
  Logger::LogInfo(*this, "Loaded points from file.");
  infile.close();
  return _particles.size();
}

void Storage::GenerateRandom(const size_t num_particles) throw(BadNewFile) {
  Logger::LogInfo(*this, "Generating new points.");
  _particles.clear();
  std::random_device dev;
  std::default_random_engine gen(dev());
  std::uniform_real_distribution<double> position_random(50.0, 150.0);
  std::uniform_real_distribution<double> velocity_random(-0.01, 0.01);

  vector<double> position, velocity;

  shared_ptr<Particle> p;
  for (int i = 0; i < num_particles; i++) {
    position = {position_random(gen), position_random(gen)};
    velocity = {velocity_random(gen), velocity_random(gen)};
    try {
      p = shared_ptr<Particle>(new Particle(position, 10, 100, velocity, 0));
    } catch (...) {
      string message = "Creating index = ";
      message += i;
      throw BadNewFile(*this, message);
    }
    AppendParticle(p);
  }
}

string Storage::GetFilename(void) const {
  return _filename;
}

const string Storage::GetObjName(void) const {
  return "GravSim::Engine::Storage";
}

vector<double> Storage::ReadDoubles(const string line) {
  vector<double> out;
  const string delimitator = " ";

  size_t start = 0;
  auto end = line.find(delimitator);
  while (end != string::npos) {
    string strvalue = line.substr(start, end - start);
    out.push_back(double(std::atof(strvalue.c_str())));

    // Update the indices.
    start = end + delimitator.length();
    end = line.find(delimitator, start);
  }
  return out;
}
