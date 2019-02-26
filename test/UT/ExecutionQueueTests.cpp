#include "catch.hpp"

#include "eul/container/observable/observing_node.hpp"
#include "eul/execution_queue.hpp"
#include "eul/function.hpp"

namespace eul
{
TEST_CASE("ExecutionQueue", "[EQ]")
{
    using ExecutionQueueType = eul::ExecutionQueue<eul::function<void(), sizeof(void*)>>;
    using ExecutorType       = typename ExecutionQueueType::ElementType;

    SECTION("push task to front")
    {
        ExecutionQueueType sut;
        bool a = false;
        bool b = false;

        ExecutorType sut.push_front([&a] { a })
    }
}
} // namespace eul
