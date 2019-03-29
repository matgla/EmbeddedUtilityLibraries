#pragma once

#include "eul/timer/observed_timer.hpp"

#include "eul/container/observable/observing_list.hpp"

namespace eul
{
namespace timer
{

class timer_manager
{
public:
    timer_manager() = default;

    void register_timer(observed_timer& timer)
    {
        timers_.push_back(timer.observing_node());
    }

    void deregister_timer(observed_timer& timer)
    {
        timer.observing_node().reset();
    }

    void run()
    {
        for (auto& timer : timers_)
        {
            timer.data()->run();
        }
    }

private:
    eul::container::observing_list<eul::container::observing_node<observed_timer*>> timers_;
};

} // namespace timer
} // namespace eul
