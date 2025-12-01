// Patterns/Observer/NotificationCenter.hpp
#pragma once
#include "ISubject.hpp"
#include <vector>
#include <memory>
#include <mutex>

class NotificationCenter : public ISubject {
private:
    std::vector<std::shared_ptr<IObserver>> observers_;
    std::mutex mtx_;
public:
    void subscribe(std::shared_ptr<IObserver> o) override;
    void unsubscribe(std::shared_ptr<IObserver> o) override;
    void publish(const std::string& event) override;
};
