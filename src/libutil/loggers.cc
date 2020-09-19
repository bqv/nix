#include "loggers.hh"

#include <nlohmann/json.hpp>

namespace nix {

// This is necessary in order to show the log format's name, rather than an
// integer, in JSON output.
NLOHMANN_JSON_SERIALIZE_ENUM(LogFormat, {
    {LogFormat::raw, "raw"},
    {LogFormat::rawWithLogs, "raw-with-logs"},
    {LogFormat::internalJson, "internal-json"},
    {LogFormat::bar, "bar"},
    {LogFormat::barWithLogs, "bar-with-logs"},
});

static std::vector<std::shared_ptr<LoggerBuilder>>* registeredLoggers;

void initRegisteredLoggers()
{
    if (!registeredLoggers)
        registeredLoggers = new std::vector<std::shared_ptr<LoggerBuilder>>();
}

void registerLogger(std::string name, std::function<Logger *()> builder)
{
    LoggerBuilder lBuilder { .name = name, .builder = builder };
    initRegisteredLoggers();
    registeredLoggers->push_back(std::make_shared<LoggerBuilder>(lBuilder));
}

std::vector<std::shared_ptr<LoggerBuilder>> getRegisteredLoggers()
{
    return *registeredLoggers;
}

}
