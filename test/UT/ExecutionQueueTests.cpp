#include "catch.hpp"

#include "eul/container/observable/observing_node.hpp"
#include "eul/execution_queue.hpp"
#include "eul/function.hpp"

TEST_CASE("ExecutionQueue", "[EQ]")
{
    using ExecutionQueueType = eul::ExecutionQueue<eul::function<void(), sizeof(void*)>>;
    using LifetimeNode       = typename ExecutionQueueType::LifetimeNodeType;

    SECTION("push task to front")
    {
        ExecutionQueueType sut;
        Lifetime bool a = false;
        bool b          = false;
        ExecutorType executor_a{[&a] { a = true; }};
        ExecutorType executor_b{[&b] { b = true; }};
        ExecutorType sut.push_front(a);
    }
}
