// Patterns/Singleton/HistoryLogger.hpp
#pragma once
#include <string>
#include <vector>
#include <mutex>

class HistoryLogger {
private:
    HistoryLogger() = default;
    std::vector<std::string> logs_;
    std::mutex m_;
public:
    static HistoryLogger& instance();
    void log(const std::string& s);
    std::vector<std::string> getLogs() const;
};
