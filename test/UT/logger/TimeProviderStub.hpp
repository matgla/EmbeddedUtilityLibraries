#pragma once 

#include <chrono>

#include <eul/time/i_time_provider.hpp>

namespace eul::logger
{
    
class TimeProviderStub : public time::i_time_provider
{
public: 
    std::chrono::milliseconds milliseconds() const;

    void set_time(std::chrono::milliseconds time);
protected: 
    std::chrono::milliseconds time_{0};
};

} // namespace eul::logger
