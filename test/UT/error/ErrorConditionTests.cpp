#include "eul/error/error_condition.hpp"
#include "eul/error/error_category.hpp"
#include "eul/error/system_category.hpp"

#include <catch.hpp>

namespace eul
{
namespace error
{

enum class MyErrors
{
    Error1 = 1,
    Error2
};

class MyCategory : public error_category
{
public:
    std::string_view name() const noexcept override
    {
        return "MyCategory";
    }

    std::string_view message(int id) const noexcept
    {
        switch (static_cast<MyErrors>(id))
        {
            case MyErrors::Error1: return "Error 1";
            case MyErrors::Error2: return "Error 2";
            default: return "Unknown error code";
        }
    }
};

MyCategory category;

template <>
error_condition make_error_condition(MyErrors e)
{
    return error_condition(static_cast<int>(e), category);
}

TEST_CASE("ErrorCondition tests", "[ErrorConditionTests]")
{
    SECTION("Should construct from enum")
    {
        error_condition ec(MyErrors::Error1);
        REQUIRE(ec);
        REQUIRE(ec.message() == "Error 1");
    }

    SECTION("Should construct from code and category")
    {
        error_condition ec(static_cast<int>(MyErrors::Error1), category);
        REQUIRE(ec);
        REQUIRE(ec.message() == "Error 1");
    }

    SECTION("Should construct from copy")
    {
        error_condition ec(static_cast<int>(MyErrors::Error2), category);
        REQUIRE(ec);
        REQUIRE(ec.message() == "Error 2");

        error_condition ec2(ec);
        REQUIRE(ec);
        REQUIRE(ec.message() == "Error 2");
    }

    SECTION("Should return false when empty")
    {
        error_condition ec;
        REQUIRE(!ec);
    }

    SECTION("Should assign value")
    {
        error_condition ec;

        ec = MyErrors::Error1;
        REQUIRE(ec.message() == "Error 1");
        REQUIRE(ec == MyErrors::Error1);

        ec.assign(static_cast<int>(MyErrors::Error2), category);
        REQUIRE(ec.message() == "Error 2");
        REQUIRE(ec == MyErrors::Error2);
    }

    SECTION("Should clear")
    {
        error_condition ec;

        ec = MyErrors::Error1;
        ec.clear();
        REQUIRE(!ec);
    }

    SECTION("Return category")
    {
        error_condition ec;

        ec = MyErrors::Error1;
        REQUIRE(ec.message() == "Error 1");
        REQUIRE(ec.category() == category);
    }
}

} // namespace error
} // namespace eul
