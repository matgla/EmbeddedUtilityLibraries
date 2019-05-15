#pragma once

#include "eul/kernel/typeid.hpp"
#include "eul/container/observable/observing_node.hpp"

namespace eul
{
namespace kernel
{

class module
{
public:
    using ModuleNode = eul::container::observing_node<module*>;

    template <typename ModuleType>
    module(typeid_t id, ModuleType& module)
        : observing_node_(this)
        , id_(id)
        , module_(&module)
    {
    }

    template <typename ModuleType>
    module(ModuleType* module)
        : observing_node_(this)
        , id_(type_id<ModuleType>())
        , module_(this)
    {
    }

    virtual ~module() = default;

    template <typename ModuleType>
    auto* get()
    {
        return static_cast<ModuleType*>(module_);
    }

    template <typename ModuleType>
    const auto* get() const
    {
        return static_cast<const ModuleType*>(module_);
    }

    ModuleNode& observing_node()
    {
        return observing_node_;
    }


    typeid_t get_id() const
    {
        return id_;
    }
private:
    ModuleNode observing_node_;
    typeid_t id_;
    void* module_;
};

} // namespace kernel
} // namespace eul
