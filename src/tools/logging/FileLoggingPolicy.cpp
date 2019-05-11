#include "FileLoggingPolicy.hpp"
#include "algorithm"

namespace tools {

namespace fs = std::filesystem;

FileLoggingPolicy::FileLoggingPolicy(const std::string& baseFileName, bool shouldUseNewFile)
{
    std::string fileFullPath;
    fs::path logsDirPath(fs::current_path() / fs::path("logs"));
    createLogsDirIfNotExists(logsDirPath);
    if(shouldUseNewFile)
        fileFullPath = getNextLogFileFullPath(logsDirPath, baseFileName);
    else
        fileFullPath = (logsDirPath / fs::path(baseFileName + "_1")).string();
    outputStream = std::ofstream(fileFullPath, std::ios::out);
}

FileLoggingPolicy::~FileLoggingPolicy() = default;

std::string FileLoggingPolicy::getNextLogFileFullPath(const fs::path& logsDir, const std::string& baseFileName) const
{
    std::vector<std::string> fileNames;
    for(auto& entryInLogsDir : fs::directory_iterator(logsDir))
        fileNames.push_back(entryInLogsDir.path().filename());

    std::vector<std::string> logFileNames;
    std::copy_if(fileNames.cbegin(), fileNames.cend(), std::back_inserter(logFileNames),
                 [&baseFileName](const auto& fileName){return fileName.find(baseFileName) != std::string::npos;});
    std::vector<int> logFileNamesSufixes;
    logFileNamesSufixes.reserve(logFileNames.size());
    std::transform(logFileNames.cbegin(), logFileNames.cend(), std::back_inserter(logFileNamesSufixes),
                   [](const auto& fileName)
                   {
                       return std::stoi(fileName.substr(fileName.rfind("_") + 1, fileName.length()));
                   });
    auto maxSuffixIt = std::max_element(logFileNamesSufixes.cbegin(), logFileNamesSufixes.cend());

    int suffix = 1;
    if(maxSuffixIt != logFileNamesSufixes.cend())
        suffix = (*maxSuffixIt) + 1;

    return (logsDir / fs::path(baseFileName + "_" + std::to_string(suffix))).string();
}

void FileLoggingPolicy::log(const char* buffer)
{
    outputStream << buffer << std::endl;
}

void FileLoggingPolicy::createLogsDirIfNotExists(fs::path& logsDirPath) const
{
    fs::create_directory(logsDirPath);
}

} // namespace tools
