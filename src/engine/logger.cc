#include "logger.hh"

#include <iostream>

using namespace GravSim::Engine;

using std::string;
using GravSim::Exception::Base;

void Logger::LogInfo(const GSObject &sender, const string message) {
  Printer("INFO", sender, message);
}

void Logger::LogWarn(const GSObject &sender, const string message) {
  Printer("WARN", sender, message);
}

void Logger::LogError(const Base &sender, const string what, const string how) {
  string message = what + how;
  Printer("ERROR", sender.who, message);
}

void Logger::Printer(
  const string type, const GSObject &sender, const string message
) {
  if (type == "ERROR") {
    std::cout << "*************************************************" << std::endl;
  }
  std::cout << type <<  ": " << sender.GetObjName() << " : " << message << std::endl;
  if (type == "ERROR") {
    std::cout << "*************************************************" << std::endl;
  }
}
