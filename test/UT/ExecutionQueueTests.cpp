#include "catch.hpp"

#include "eul/container/observable/observing_node.hpp"
#include "eul/execution_queue.hpp"
#include "eul/function.hpp"

TEST_CASE("ExecutionQueue", "[EQ]")
{
    using ExecutionQueueType = eul::execution_queue<eul::function<void(), sizeof(void*) * 4>, 3>;
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
        int a              = 0;
        int b              = 0;
        int c              = 0;
        static int counter = 0;
        ExecutionQueueType sut;

        LifetimeNode lifetime;
        sut.push_front(lifetime, [&a] { a = ++counter; });
        sut.push_front(lifetime, [&b, &c, &lifetime, &sut] {
            sut.push_front(lifetime, [&c] { c = ++counter; });
            b = ++counter;
        });

        sut.run();

        REQUIRE(a == 3);
        REQUIRE(b == 1);
        REQUIRE(c == 2);
    }

    SECTION("push_back while execution ongoing")
    {
        int a              = 0;
        int b              = 0;
        int c              = 0;
        static int counter = 0;
        ExecutionQueueType sut;

        LifetimeNode lifetime;
        sut.push_front(lifetime, [&a] { a = ++counter; });
        sut.push_front(lifetime, [&b, &c, &lifetime, &sut] {
            sut.push_back(lifetime, [&c] { c = ++counter; });
            b = ++counter;
        });

        sut.run();

        REQUIRE(a == 2);
        REQUIRE(b == 1);
        REQUIRE(c == 3);
    }

    SECTION("return false when buffor too small")
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
