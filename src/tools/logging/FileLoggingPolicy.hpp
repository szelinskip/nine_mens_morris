#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "LoggingPolicy.hpp"

namespace tools {

class FileLoggingPolicy : public LoggingPolicy
{
public:
    FileLoggingPolicy(const std::string& baseFileName, bool shouldUseNewFile);

    virtual ~FileLoggingPolicy() override;

    FileLoggingPolicy() = delete;
    FileLoggingPolicy(const FileLoggingPolicy&) = delete;
    FileLoggingPolicy& operator=(const FileLoggingPolicy&) = delete;
    FileLoggingPolicy(FileLoggingPolicy&&) = delete;
    FileLoggingPolicy& operator=(FileLoggingPolicy&&) = delete;

    virtual void log(const char* buffer) override;

private:
    void createLogsDirIfNotExists(std::filesystem::path& logsDirPath) const;
    std::string getNextLogFileFullPath(const std::filesystem::path& logsDir, const std::string& baseFileName) const;

    std::ofstream outputStream;
};

} // namespace tools
