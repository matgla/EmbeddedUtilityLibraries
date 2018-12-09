#pragma once

namespace eul
{

template <typename... Observers>
struct Observer : Observers...
{
    using Observers::operator()...;
};

template <typename... Observers>
Observer(Observers...)->Observer<Observers...>;

} // namespace eul
