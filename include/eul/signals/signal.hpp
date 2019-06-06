#pragma once

#include "eul/function.hpp"
#include "eul/container/observable/observing_list.hpp"

#include "eul/signals/slot.hpp"

namespace eul
{
namespace signals
{

template <class, std::size_t Size = 1>
class signal;

template <std::size_t Size, class ReturnType, class... Args>
class signal<ReturnType(Args...), Size>
{
public:
    using slot_t = slot<ReturnType(Args...), Size>;

    void connect(slot_t& slot)
    {
        slots_.push_back(slot.observing_node());
    }

    void emit(Args&&... args) const
    {
        for (const auto& slot_observer : slots_)
        {
            const auto& slot = *(slot_observer.data());
            slot(std::forward<Args>(args)...);
        }
    }

private:
    using observing_list = eul::container::observing_list<typename slot_t::observed_type>;
    observing_list slots_;
};

} // namespace signals
} // namespace eul
