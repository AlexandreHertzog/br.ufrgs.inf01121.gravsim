#include "logger.hh"

#include <iostream>

using namespace GravSim::Engine;

void Logger::LoggerInit(void) {
  //using namespace std::placeholders;
  //LogError = std::bind(Printer, "ERROR", _1, _2);
  //LogWarn = std::bind(Printer, "WARN", _1, _2);
  //LogInfo = std::bind(Printer, "INFO", _1, _2);
}

void Logger::LogInfo(const GSObject &sender, const std::string message) {
  Printer("INFO", sender, message);
}

void Logger::LogWarn(const GSObject &sender, const std::string message) {
  Printer("WARN", sender, message);
}

void Logger::LogError(const GSObject &sender, const std::string message) {
  Printer("ERROR", sender, message);
}

void Logger::Printer(
  const std::string type, const GSObject &sender, const std::string message
) {
  if (type == "ERROR") {
    std::cout << "*************************************************" << std::endl;
  }
  std::cout << type <<  ": " << sender.GetObjName() << " : " << message << std::endl;
  if (type == "ERROR") {
    std::cout << "*************************************************" << std::endl;
  }
}
