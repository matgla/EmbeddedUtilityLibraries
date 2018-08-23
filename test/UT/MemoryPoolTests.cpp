#include "catch.hpp"

#include "eul/memory_pool.hpp"

class ConstructorTester
{
public:
    ConstructorTester()
        : constructed_(true)
    {
    }

    constexpr bool constructed() const
    {
        return constructed_;
    }

private:
    bool constructed_ = false;
};

TEST_CASE("MemoryPool should", "[MemoryPool]")
{
    SECTION("call constructor")
    {
        eul::MemoryPool<128> sut;
        auto* test = sut.allocate<ConstructorTester>();
        // REQUIRE(test->constructed());
    }
}
