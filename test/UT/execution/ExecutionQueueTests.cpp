#include "catch.hpp"

#include "eul/container/observable/observing_node.hpp"
#include "eul/execution/execution_queue.hpp"
#include "eul/function.hpp"

TEST_CASE("ExecutionQueue", "[EQ]")
{
    using ExecutionQueueType = eul::execution::execution_queue<3>;
    using LifetimeNode       = typename ExecutionQueueType::LifetimeNodeType;

    SECTION("push task to front")
    {
        ExecutionQueueType sut;
        LifetimeNode lifetime;
        bool a = false;
        bool b = false;
        sut.push_front(lifetime, [&a] { a = true; });
        sut.push_front(lifetime, [&b] { b = true; });
        sut.run();

        REQUIRE(a == true);
        REQUIRE(b == true);
    }

    SECTION("not run if lifetime ends ealier")
    {
        bool a = false;
        bool b = false;

        ExecutionQueueType sut;
        {
            LifetimeNode lifetime;
            sut.push_front(lifetime, [&a] { a = true; });
            sut.run();
            sut.push_front(lifetime, [&b] { b = true; });
        }
        sut.run();

        REQUIRE(a == true);
        REQUIRE(b == false);
    }

    SECTION("not run front if lifetime ends ealier")
    {
        bool a = false;
        bool b = false;

        ExecutionQueueType sut;
        {
            LifetimeNode lifetime;
            sut.push_front(lifetime, [&a] { a = true; });
            sut.push_front(lifetime, [&b] { b = true; });
        }
        sut.run();

        REQUIRE(a == false);
        REQUIRE(b == false);
    }

    SECTION("push_front while execution ongoing")
    {
        struct Data
        {
            int a              = 0;
            int b              = 0;
            int c              = 0;
            LifetimeNode lifetime;
            ExecutionQueueType sut;
        };

        static int counter = 0;
        Data data;
        auto& sut = data.sut;

        sut.push_front(data.lifetime, [&data] { data.a = ++counter; });
        sut.push_front(data.lifetime, [&data] {
            data.sut.push_front(data.lifetime, [&data] { data.c = ++counter; });
            data.b = ++counter;
        });

        sut.run();

        REQUIRE(data.a == 3);
        REQUIRE(data.b == 1);
        REQUIRE(data.c == 2);
    }

    SECTION("push_back while execution ongoing")
    {
        struct Data
        {
            int a              = 0;
            int b              = 0;
            int c              = 0;
            LifetimeNode lifetime;
            ExecutionQueueType sut;
        };

        static int counter = 0;
        Data data;
        auto& sut = data.sut;

        sut.push_front(data.lifetime, [&data] { data.a = ++counter; });
        sut.push_front(data.lifetime, [&data] {
            data.sut.push_back(data.lifetime, [&data] { data.c = ++counter; });
            data.b = ++counter;
        });

        sut.run();

        REQUIRE(data.a == 2);
        REQUIRE(data.b == 1);
        REQUIRE(data.c == 3);
    }

    SECTION("return false when buffer too small")
    {
        ExecutionQueueType sut;
        LifetimeNode lifetime;
        REQUIRE(sut.push_front(lifetime, [] {}));
        REQUIRE(sut.push_front(lifetime, [] {}));
        REQUIRE(sut.push_front(lifetime, [] {}));
        REQUIRE(sut.push_front(lifetime, [] {}) == false);
        REQUIRE(sut.push_back(lifetime, [] {}) == false);
    }
}
