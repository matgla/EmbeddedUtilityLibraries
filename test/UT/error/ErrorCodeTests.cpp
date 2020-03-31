#include "eul/error/error_code.hpp"
#include "eul/error/system_category.hpp"

#include <catch.hpp>

namespace eul
{
namespace error
{

TEST_CASE("ErrorCode tests", "[ErrorCodeTests]")
{
    SECTION("Should construct from enum")
    {
        error_code ec(error::errc::permision_denied);
        REQUIRE(ec);
        REQUIRE(ec.message() == "Permission denied");
    }

    SECTION("Should construct from code and category")
    {
        system_category cat;
        error_code ec(1, cat);
        REQUIRE(ec);
        REQUIRE(ec.message() == "Permission denied");
    }
}

} // namespace error
} // namespace eul
