#pragma once

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node.hpp"
#include "eul/function.hpp"

namespace eul
{
namespace execution
{

class i_execution_queue
{
public:
    using LifetimeNodeType = eul::container::observing_node<bool>;
    using ExecutorType = eul::function<void(), sizeof(void*)>;

    virtual ~i_execution_queue() = default;

    virtual bool push_back(LifetimeNodeType& lifetime, const ExecutorType& executor) = 0;
    virtual bool push_front(LifetimeNodeType& lifetime, const ExecutorType& executor) = 0;
    virtual void run() = 0;
};

} // namespace execution
} // namespace eul
