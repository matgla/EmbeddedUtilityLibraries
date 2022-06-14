#include "eul/filesystem/path_const_iterator.hpp"

#include <catch2/catch_test_macros.hpp>

namespace eul::filesystem
{

TEST_CASE("PathConstIteratorShould", "[PathConstTests]")
{
    SECTION("ReturnsEmptyForEmptyPath")
    {
        path_const_iterator it("");
        REQUIRE(*it.empty());

    }
    SECTION("ReturnsRootPath")
    {
        path_const_iterator it("///");
        REQUIRE(*it == "/");
        REQUIRE(*(++it).empty());
    }
    SECTION("ReturnsPathUnderRoot")
    {
        path_const_iterator it("///dir//");
        REQUIRE(*it++ == "/");
        REQUIRE(*it++ == "dir");
        REQUIRE((*it).empty());
    }
    SECTION("ReturnsCorrectPartsOfPath")
    {
        path_const_iterator it("///a////b//c/../d/.//../d///.//");
        REQUIRE(*it++ == "/");
        REQUIRE(*it++ == "a");
        REQUIRE(*it++ == "b");
        REQUIRE(*it++ == "c");
        REQUIRE(*it++ == "..");
        REQUIRE(*it++ == "d");
        REQUIRE(*it++ == ".");
        REQUIRE(*it++ == "..");
        REQUIRE(*it++ == "d");
        REQUIRE(*it++ == ".");
    }
    SECTION("ReturnsCorrectPartsOfRelativePath")
    {
        path_const_iterator it("a/.");
        REQUIRE(*it++ == "a");
        REQUIRE(*it++ == ".");
        REQUIRE(*(it++).empty());
    }
}

} // namespace eul::filesystem
