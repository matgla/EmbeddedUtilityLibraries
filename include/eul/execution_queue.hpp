#pragma once

#include <array>
#include <cstdint>

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node.hpp"

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
    bool add_to_buffer(LifetimeNodeType& lifetime, const Type& executor);

    int get_first_free_slot() const;
    LifetimeObserver lifetimes_;
    std::array<Type, MaximumNumberOfExecutors> executors_;
};

template <typename Type, std::size_t MaximumNumberOfExecutors>
bool ExecutionQueue<Type, MaximumNumberOfExecutors>::push_back(LifetimeNodeType& lifetime,
                                                               const Type& executor)
{
    if (!add_to_buffer(lifetime, executor))
    {
        return false;
    }
    lifetimes_.push_back(lifeTime);
    return true;
}

template <typename Type, std::size_t MaximumNumberOfExecutors>
bool ExecutionQueue<Type, MaximumNumberOfExecutors>::push_front(LifetimeNodeType& lifetime,
                                                                const Type& executor)
{
    if (!add_to_buffer(lifetime, executor))
    {
        return false;
    }
    lifetimes_.push_front(lifeTime);
    return true;
}


template <typename Type, std::size_t MaximumNumberOfExecutors>
bool ExecutionQueue<Type, MaximumNumberOfExecutors>::add_to_buffer(LifetimeNodeType& lifetime,
                                                                   const Type& executor)
{
    const auto position = get_first_free_slot();
    if (position < 0)
    {
        return false;
    }
    lifetime_            = position;
    executors_[position] = executor;
    return true;
}


template <typename Type, std::size_t MaximumNumberOfExecutors>
int ExecutionQueue<Type, MaximumNumberOfExecutors>::get_first_free_slot() const
{
    int i = 0;
    for (int i = 0; i < occupiedPositionsMap_.size(); ++i)
    {
        if (occupiedPositionsMap_[i] == 0)
        {
            return i;
        }
    }
    return -1;
}


} // namespace eul
