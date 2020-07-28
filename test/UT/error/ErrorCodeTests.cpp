#include "eul/error/error_code.hpp"
#include "eul/error/system_category.hpp"

#include <catch.hpp>

namespace eul::error
{

TEST_CASE("ErrorCode tests", "[ErrorCodeTests]")
{
    SECTION("Should construct from enum")
    {
        error_code ec(error::errc::permission_denied);
        REQUIRE(ec);
        REQUIRE(ec.message() == "Permission denied");
    }

    SECTION("Should construct from code and category")
    {
        error_code ec(static_cast<int>(errc::permission_denied), system_category());
        REQUIRE(ec);
        REQUIRE(ec.message() == "Permission denied");
    }

    SECTION("Should return false when empty")
    {
        error_code ec;
        REQUIRE(!ec);
    }

    SECTION("Should assign value")
    {
        error_code ec;

        ec = error::errc::permission_denied;
        REQUIRE(ec.message() == "Permission denied");
        REQUIRE(ec == errc::permission_denied);

        ec.assign(static_cast<int>(error::errc::argument_list_to_long), system_category());
        REQUIRE(ec.message() == "Argument list to big");
        REQUIRE(ec == errc::argument_list_to_long);
    }

    SECTION("Should clear")
    {
        error_code ec;

        ec = error::errc::permission_denied;
        ec.clear();
        REQUIRE(!ec);
    }

    SECTION("Return category")
    {
        error_code ec;

        ec = error::errc::permission_denied;
        REQUIRE(ec.message() == "Permission denied");
        REQUIRE(ec.category() == system_category());
    }
}

} // namespace eul::error
