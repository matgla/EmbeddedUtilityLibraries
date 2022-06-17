#include "eul/error/error_category.hpp"

#include <catch2/catch_test_macros.hpp>

namespace eul::error
{

enum class MyErrors
{
    SomeError1 = 1,
    SomeError2
};

enum class MyErrors2
{
    SomeError1 = 1,
    SomeError2
};


class MyErrorCategory1 : public error_category
{
public:
    [[nodiscard]]
    std::string_view name() const noexcept override
    {
        return "MyErrorCategory1";
    }

    [[nodiscard]]
    std::string_view message(int condition) const override
    {
        switch (static_cast<MyErrors>(condition))
        {
            case MyErrors::SomeError1: return "Category 1 Error 1";
            case MyErrors::SomeError2: return "Category 1 Error 2";
            default: return "Unknown error";
        }
    }
};

class MyErrorCategory2 : public error_category
{
public:
    [[nodiscard]]
    std::string_view name() const noexcept override
    {
        return "MyErrorCategory2";
    }

    [[nodiscard]]
    std::string_view message(int condition) const override
    {
        switch (static_cast<MyErrors2>(condition))
        {
            case MyErrors2::SomeError1: return "Category 2 Error 1";
            case MyErrors2::SomeError2: return "Category 2 Error 2";
            default: return "Unknown error";
        }
    }
};

TEST_CASE("ErrorCategory tests", "[ErrorCategoryTests]")
{
    SECTION("Should return category name")
    {
        MyErrorCategory1 sut_1;
        MyErrorCategory2 sut_2;


        error_category& base_1 = sut_1;
        error_category& base_2 = sut_2;
        REQUIRE(sut_1.name() == "MyErrorCategory1");
        REQUIRE(sut_2.name() == "MyErrorCategory2");
        REQUIRE(base_1.name() == "MyErrorCategory1");
        REQUIRE(base_2.name() == "MyErrorCategory2");
    }

    SECTION("Should translate to message")
    {
        MyErrorCategory1 sut_1;
        MyErrorCategory2 sut_2;

        error_category& base_1 = sut_1;
        error_category& base_2 = sut_2;
        REQUIRE(sut_1.message(1) == "Category 1 Error 1");
        REQUIRE(sut_1.message(2) == "Category 1 Error 2");
        REQUIRE(sut_2.message(1) == "Category 2 Error 1");
        REQUIRE(sut_2.message(2) == "Category 2 Error 2");

        REQUIRE(base_1.message(1) == "Category 1 Error 1");
        REQUIRE(base_1.message(2) == "Category 1 Error 2");
        REQUIRE(base_2.message(1) == "Category 2 Error 1");
        REQUIRE(base_2.message(2) == "Category 2 Error 2");
    }

    SECTION("Should compare")
    {
        MyErrorCategory1 sut_1;
        MyErrorCategory2 sut_2;

        error_category& base_1 = sut_1;
        error_category& base_2 = sut_2;
        REQUIRE(sut_1 == base_1);
        REQUIRE(sut_2 == base_2);
        REQUIRE(sut_1 != sut_2);
        /* depends of architecture addressing */
        if (std::less<>()(&base_1, &sut_2))
        {
            REQUIRE(base_1 < sut_2);
        }
        else
        {
            REQUIRE(sut_2 < base_1);
        }

        auto val = sut_1 <=> sut_2;
        REQUIRE((val < 0));
        val = sut_2 <=> sut_1;
        REQUIRE((val > 0));
        val = sut_1 <=> sut_1;
        REQUIRE((val == 0));

    }
}

} // namespace eul::error
