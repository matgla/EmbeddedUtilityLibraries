#pragma once

#include <memory>
#include <string_view>
#include <type_traits>
#include <tuple>

#include "eul/assert.hpp"
#include "eul/kernel/typeid.hpp"
#include "eul/kernel/module.hpp"
#include "eul/kernel/event_listener.hpp"
#include "eul/container/observable/observing_list.hpp"

namespace eul
{
namespace kernel
{

class Kernel
{
public:
    void register_module(Module& module)
    {
        modules_.push_back(module.observing_node());
    }

    template <typename ModuleType>
    const ModuleType* get_module() const
    {
        const auto module_id = type_id<ModuleType>();

        for (auto& module : modules_)
        {
            if (module.data()->get_id() == module_id)
            {
                return module.data()->get<ModuleType>();
            }
        }
        EUL_ASSERT_MSG(false, "Trying to retrieve unregistered module");
        return nullptr;
    }

    template <typename ModuleType>
    ModuleType* get_module()
    {
        const auto module_id = type_id<ModuleType>();

        for (auto& module : modules_)
        {
            if (module.data()->get_id() == module_id)
            {
                return module.data()->get<ModuleType>();
            }
        }
        EUL_ASSERT_MSG(false, "Trying to retrieve unregistered module");
        return nullptr;
    }

    template <typename EventType>
    constexpr void post_event(const EventType& event) const
    {
        if (EventListener<EventType>::listener)
        {
            EventListener<EventType>::listener->handle_event(event);
        }
    }

private:
    eul::container::observing_list<eul::container::observing_node<Module*>> modules_;
};


} // namespace kernel
} // namespace eul
