#pragma once

namespace eul
{
namespace logger
{

class suppressing_logger
{
public:
    template <typename T>
    const suppressing_logger& operator<<(const T& str) const
    {
        UNUSED(str);
        return *this;
    }
};

} // namespace logger
} // namespace eul
