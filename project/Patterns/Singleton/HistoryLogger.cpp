// Patterns/Singleton/HistoryLogger.cpp
#include "HistoryLogger.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>

HistoryLogger& HistoryLogger::instance() {
    static HistoryLogger inst;
    return inst;
}

static std::string nowStr() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void HistoryLogger::log(const std::string& s) {
    std::lock_guard<std::mutex> lk(m_);
    logs_.push_back(nowStr() + " - " + s);
}

std::vector<std::string> HistoryLogger::getLogs() const {
    return logs_;
}
