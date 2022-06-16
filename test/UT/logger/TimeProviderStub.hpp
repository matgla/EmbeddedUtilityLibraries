#pragma once 

#include <eul/time/i_time_provider.hpp>

namespace eul::logger
{
    
class TimeProviderStub : public time::i_time_provider
{
public: 
    std::chrono::milliseconds milliseconds() const;
};

} // namespace eul::logger
