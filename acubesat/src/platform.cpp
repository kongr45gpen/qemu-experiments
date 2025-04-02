#include "etl/String.hpp"
#include "ECSS_Definitions.hpp"
#include "Logger.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "Definitions.hpp"

void Logger::log(Logger::LogLevel level, etl::istring &message) {
    etl::string<15> levelString;
    etl::string<10> time;

    if (level <= Logger::trace) {
        levelString.append("trace");
    } else if (level <= Logger::debug) {
        levelString.append("debug");
    } else if (level <= Logger::info) {
        levelString.append("info");
    } else if (level <= Logger::notice) {
        levelString.append("notice");
    } else if (level <= Logger::warning) {
        levelString.append("warning");
    } else if (level <= Logger::error) {
        levelString.append("error");
    } else {
        levelString = "emergency";
    }

    while (levelString.available()) {
        levelString.append(" ");
    }

    etl::to_string(xTaskGetTickCount(), time, format.width(10), 0);

    etl::string<LOGGER_MAX_MESSAGE_SIZE> output;
    output.append(time.c_str());
    output.append(" [");
    output.append(levelString.c_str());
    output.append("] ");

    etl::string<LogSource::MaximumLettersInSubsystemName + 1> subsystemString = LogSource::currentSubsystem;
    if (LogSource::currentSubsystem.empty()) {
        subsystemString = "None ";
    }
    while (subsystemString.available()) {
        subsystemString.append(" ");
    }
    output.append(subsystemString.c_str());

    output.append(message.c_str());
    output.append("\n");

    printf("%s", output.c_str());
}

template<>
void convertValueToString(String<LOGGER_MAX_MESSAGE_SIZE>& message, char* value) {
    message.append(value);
}

template<>
void convertValueToString(String<LOGGER_MAX_MESSAGE_SIZE>& message, const char* value)  {
    message.append(value);
}
