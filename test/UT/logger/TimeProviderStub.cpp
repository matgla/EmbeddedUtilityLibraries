#include "TimeProviderStub.hpp"

namespace eul::logger
{
    
std::chrono::milliseconds TimeProviderStub::milliseconds() const 
{
    return {};
}

} // namespace eul::logger
