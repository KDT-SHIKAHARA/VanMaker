#pragma once
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <functional>
#include <algorithm>

#include"singleton.h"

class EventBus : public Singleton<EventBus> {
    friend class Singleton<EventBus>;
    EventBus() = default;
    ~EventBus() = default;

public:

    template<typename EventType>
    void Subscribe(std::function<void(const EventType&)> callback) {
        auto& vec = subscribers_[typeid(EventType)];
        vec.push_back([cb = std::move(callback)](const void* e) {
            cb(*static_cast<const EventType*>(e));
            });
    }

    template<typename EventType>
    void Publish(const EventType& event) {
        auto it = subscribers_.find(typeid(EventType));
        if (it != subscribers_.end()) {
            for (auto& func : it->second) {
                func(&event);
            }
        }
    }

private:

    std::unordered_map<std::type_index, std::vector<std::function<void(const void*)>>> subscribers_;
};
