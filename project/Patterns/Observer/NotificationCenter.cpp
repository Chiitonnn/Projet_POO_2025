// Patterns/Observer/NotificationCenter.cpp
#include "NotificationCenter.hpp"
#include <algorithm>
#include <iostream>

void NotificationCenter::subscribe(std::shared_ptr<IObserver> o) {
    std::lock_guard<std::mutex> lk(mtx_);
    observers_.push_back(o);
}
void NotificationCenter::unsubscribe(std::shared_ptr<IObserver> o) {
    std::lock_guard<std::mutex> lk(mtx_);
    observers_.erase(std::remove(observers_.begin(), observers_.end(), o), observers_.end());
}
void NotificationCenter::publish(const std::string& event) {
    std::lock_guard<std::mutex> lk(mtx_);
    for (auto& o : observers_) {
        if (o) o->notify(event);
    }
}
