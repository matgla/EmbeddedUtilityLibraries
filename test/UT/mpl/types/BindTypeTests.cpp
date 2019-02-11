#include <string>
#include <type_traits>

#include <catch.hpp>

#include "eul/mpl/types/bind_type.hpp"

namespace eul
{
namespace mpl
{
namespace types
{

TEST_CASE("BindType should", "[BindType]")
{
    SECTION("Bind value to type")
    {
        class Logger;
        class LoggerImplementation
        {
        public:
            LoggerImplementation(const std::string& name) : name_(name)
            {
            }
            const std::string& get_name() const { return name_; }
        private:
            std::string name_;
        };

        auto binded = bind_type<Logger>::to(LoggerImplementation("MyAwesomeLogger"));

        REQUIRE(binded.value.get_name() == "MyAwesomeLogger");
        using BindedType = decltype(binded);
        REQUIRE(std::is_same<LoggerImplementation, BindedType::ValueType>::value);
        REQUIRE(std::is_same<Logger, BindedType::KeyType>::value);
    }
}

} // namespace types
} // namespace mpl
} // namespace eul
