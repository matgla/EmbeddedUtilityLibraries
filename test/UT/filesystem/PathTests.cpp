#include "eul/filesystem/path.hpp"

#include <catch.hpp>

namespace eul
{
namespace filesystem
{

TEST_CASE("Path should", "[FilesystemTests]")
{
    SECTION("Return lexically normal path")
    {
        path test_path("/./this///.../is///some/../../is../path/to/a//../..");
        REQUIRE(test_path.lexically_normal().native() == "/this/.../is../path");
    }
    SECTION("Return lexically normal path for empty")
    {
        path test_path("");
        REQUIRE(test_path.lexically_normal().native() == "");
    }
    SECTION("Return lexically normal path for root")
    {
        path test_path("/");
        REQUIRE(test_path.lexically_normal().native() == "/");
    }
    SECTION("Return lexically normal path for realtive path")
    {
        path test_path("this/is/../relative/path");
        REQUIRE(test_path.lexically_normal().native() == "this/relative/path");
    }
    SECTION("Return . path when relative path back to much")
    {
        path test_path("this/is/../..");
        REQUIRE(test_path.lexically_normal().native() == ".");
    }
    SECTION("Return .. path when relative path back to much")
    {
        path test_path("this/is/../../..");
        REQUIRE(test_path.lexically_normal().native() == "..");
    }
    SECTION("Return ../.. path when relative path back to much")
    {
        path test_path("this/is/../../../..");
        REQUIRE(test_path.lexically_normal().native() == "../..");
    }
    SECTION("Return / path when absolute path back to much")
    {
        path test_path("/this/is/../../..");
        REQUIRE(test_path.lexically_normal().native() == "/");
    }
    SECTION("Return / path when absolute path back to much")
    {
        path test_path("/this/is/../../../..");
        REQUIRE(test_path.lexically_normal().native() == "/");
    }
    SECTION("Return .. path when ..")
    {
        path test_path("..");
        REQUIRE(test_path.lexically_normal().native() == "..");
    }
    SECTION("Return ../.. path when ../..")
    {
        path test_path("..");
        REQUIRE(test_path.lexically_normal().native() == "..");
    }
    SECTION("Return / path when /..")
    {
        path test_path("/..");
        REQUIRE(test_path.lexically_normal().native() == "/");
    }
    SECTION("Return / path when /../..")
    {
        path test_path("/../..");
        REQUIRE(test_path.lexically_normal().native() == "/");
    }
    SECTION("Iterate through path")
    {
        path test_path1("///a////b//c/../d/./../d///.//");

        path_const_iterator it = test_path1.begin();
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
        REQUIRE(it == test_path1.end());

        path test_path2("/");
        it = test_path2.begin();
        REQUIRE(*it++ == "/");
        REQUIRE(it == test_path2.end());

        path test_path3("/abc");
        it = test_path3.begin();
        REQUIRE(*it++ == "/");
        REQUIRE(*it++ == "abc");
        REQUIRE(it == test_path3.end());

        path test_path4("");
        it = test_path4.begin();
        REQUIRE(it == test_path4.end());
    }
    SECTION("Return absolute path when slash is at begin")
    {
        REQUIRE(path("/test").is_absolute());
        REQUIRE(!path("est").is_absolute());
    }
}

} // namespace filesystem
} // namespace eul
