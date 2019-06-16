#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <utility>

#include "eul/execution/i_execution_queue.hpp"
#include "eul/container/static_deque.hpp"
#include "eul/function.hpp"

namespace eul
{
namespace execution
{

template <std::size_t MaximumNumberOfExecutors>
class execution_queue : public i_execution_queue
{
public:
    bool push_back(LifetimeNodeType& lifetime, const ExecutorType& executor) override;
    bool push_front(LifetimeNodeType& lifetime, const ExecutorType& executor) override;

    void run() override;

private:
    using LifetimeObserver = eul::container::observing_list<LifetimeNodeType>;
    LifetimeObserver lifetimes_;
    using Execution = std::pair<LifetimeNodeType*, ExecutorType>;
    container::static_deque<Execution, MaximumNumberOfExecutors> executors_;
};

template <std::size_t MaximumNumberOfExecutors>
bool execution_queue<MaximumNumberOfExecutors>::push_back(LifetimeNodeType& lifetime,
                                                                const ExecutorType& executor)
{
    if (executors_.size() == executors_.max_size())
    {
        return false;
    }

    executors_.push_back(std::make_pair(&lifetime, executor));
    lifetimes_.push_back(lifetime);
    return true;
}

template <std::size_t MaximumNumberOfExecutors>
bool execution_queue<MaximumNumberOfExecutors>::push_front(LifetimeNodeType& lifetime,
                                                                 const ExecutorType& executor)
{
    if (executors_.size() == executors_.max_size())
    {
        return false;
    }

    executors_.push_front(std::make_pair(&lifetime, executor));
    lifetimes_.push_front(lifetime);
    return true;
}

template <std::size_t MaximumNumberOfExecutors>
void execution_queue<MaximumNumberOfExecutors>::run()
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

} // namespace execution
} // namespace eul