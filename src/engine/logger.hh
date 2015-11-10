#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <functional>

#include "gsobject.hh"

namespace GravSim {
namespace Engine {
namespace Logger {
static void LoggerInit(void);
//static std::function<void(const std::string, const std::string)> LogError;
//static std::function<void(const std::string, const std::string)> LogWarn;
//static std::function<void(const std::string, const std::string)> LogInfo;
void LogInfo(const GSObject &obj, const std::string message);
void LogWarn(const GSObject &obj, const std::string message);
void LogError(const GSObject &obj, const std::string message);
static void Printer(
	const std::string type, const GSObject &sender,
	const std::string message 
);

} // namespace Logger
} // namespace Engine
} // namespace GravSim

#endif
