#pragma once

#include <array>
#include <cstdint>

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node.hpp"
#include "eul/container/static_deque.hpp"

namespace eul
{

template <typename Type, std::size_t MaximumNumberOfExecutors>
class ExecutionQueue
{
protected:
    using LifetimeObserver = eul::container::observing_list<LifetimeNodeType>;
    using PositionType     = uint16_t;

public:
    using LifetimeNodeType = eul::container::observing_node<PositionType>;

    bool push_back(LifetimeNodeType& lifetime, const Type& executor);
    bool push_front(LifetimeNodeType& lifetime, const Type& executor);

    void run();

private:
    LifetimeObserver lifetimes_;
    container::static_deque<Type, MaximumNumberOfExecutors> executors_;
};

template <typename Type, std::size_t MaximumNumberOfExecutors>
bool ExecutionQueue<Type, MaximumNumberOfExecutors>::push_back(LifetimeNodeType& lifetime,
                                                               const Type& executor)
{
    if (executors_.size() == executors_.max_size())
    {
        return false;
    }
    executors_.push_back(executor);
    lifetimes_.push_back(lifeTime);
    return true;
}

template <typename Type, std::size_t MaximumNumberOfExecutors>
bool ExecutionQueue<Type, MaximumNumberOfExecutors>::push_front(LifetimeNodeType& lifetime,
                                                                const Type& executor)
{
    if (executors_.size() == executors_.max_size())
    {
        return false;
    }
    executors_.push_front(executor);
    lifetimes_.push_front(lifeTime);
    return true;
}


} // namespace eul
