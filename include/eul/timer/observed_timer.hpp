#pragma once

#include "eul/timer/ITimer.hpp"

#include "eul/container/observable/observing_node.hpp"

namespace eul
{
namespace timer
{

class observed_timer : public ITimer
{
public:
    observed_timer()
        : observing_node_(this)
    {
    }

    eul::container::observing_node<observed_timer*>& observing_node()
    {
        return observing_node_;
    }

protected:
    eul::container::observing_node<observed_timer*> observing_node_;
};

} // namespace timer
} // namespace eul
