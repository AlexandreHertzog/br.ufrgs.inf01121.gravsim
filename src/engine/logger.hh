#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <functional>

#include "gsobject.hh"
#include "base.hh"

namespace GravSim {
namespace Engine {
namespace Logger {

void LogInfo(const GSObject &obj, const std::string message);
void LogWarn(const GSObject &obj, const std::string message);
void LogError(const GravSim::Exception::Base &except, const std::string what, const std::string how);
void Printer(
  const std::string type, const GSObject &sender,
  const std::string message 
);

} // namespace Logger
} // namespace Engine
} // namespace GravSim

#endif
