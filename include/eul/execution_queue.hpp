#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <utility>

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node.hpp"
#include "eul/container/static_deque.hpp"

namespace eul
{

template <typename Type, std::size_t MaximumNumberOfExecutors>
class execution_queue
{
public:
    using LifetimeNodeType = eul::container::observing_node<bool>;

public:
    bool push_back(LifetimeNodeType& lifetime, const Type& executor);
    bool push_front(LifetimeNodeType& lifetime, const Type& executor);

    void run();

private:
    using LifetimeObserver = eul::container::observing_list<LifetimeNodeType>;
    LifetimeObserver lifetimes_;
    using Execution = std::pair<LifetimeNodeType*, Type>;
    container::static_deque<Execution, MaximumNumberOfExecutors> executors_;
};

template <typename Type, std::size_t MaximumNumberOfExecutors>
bool execution_queue<Type, MaximumNumberOfExecutors>::push_back(LifetimeNodeType& lifetime,
                                                                const Type& executor)
{
    if (executors_.size() == executors_.max_size())
    {
        return false;
    }

    executors_.push_back(std::make_pair(&lifetime, executor));
    lifetimes_.push_back(lifetime);
    return true;
}

template <typename Type, std::size_t MaximumNumberOfExecutors>
bool execution_queue<Type, MaximumNumberOfExecutors>::push_front(LifetimeNodeType& lifetime,
                                                                 const Type& executor)
{
    if (executors_.size() == executors_.max_size())
    {
        return false;
    }

    executors_.push_front(std::make_pair(&lifetime, executor));
    lifetimes_.push_front(lifetime);
    return true;
}

template <typename Type, std::size_t MaximumNumberOfExecutors>
void execution_queue<Type, MaximumNumberOfExecutors>::run()
{
    while (executors_.size())
    {
        if (lifetimes_.find(executors_.front().first) == nullptr)
        {
            executors_.pop_front();
        }
        else
        {
            auto executor  = executors_.front().second;
            auto* lifetime = executors_.front().first;
            if (std::find_if(executors_.begin(), executors_.end(), [lifetime](const auto& executor) {
                    return lifetime == executor.first;
                }) == executors_.end())
            {
                lifetimes_.erase(*lifetime);
            }
            executors_.pop_front();
            executor();
        }
    }
}

} // namespace eul
