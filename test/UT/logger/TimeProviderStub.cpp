#include "TimeProviderStub.hpp"

namespace eul::logger
{
    
std::chrono::milliseconds TimeProviderStub::milliseconds() const 
{
    return time_;
}

void TimeProviderStub::set_time(std::chrono::milliseconds time)
{
    time_ = time;
}


} // namespace eul::logger
