#pragma once

#include "eul/timer/observed_timer.hpp"

#include "eul/container/observable/observing_list.hpp"

namespace eul
{
namespace timer
{
class TimerManager
{
public:
    TimerManager() = default;

    void register_timer(ObservedTimer& timer)
    {
        timers_.push_back(timer.observing_node());
    }

    void deregister_timer(ObservedTimer& timer)
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
    eul::container::observing_list<eul::container::observing_node<ObservedTimer*>> timers_;
};

} // namespace timer
} // namespace eul
