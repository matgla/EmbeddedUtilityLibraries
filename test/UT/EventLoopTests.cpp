// #include <catch.hpp>
// #include <fakeit.hpp>
// 
// #include "eul/event_loop.hpp"
// #include "eul/function.hpp"
// using namespace fakeit;
// 
// 
// struct CallMeInterface
// {
//     virtual void a()    = 0;
//     virtual void b()    = 0;
//     virtual void c(int) = 0;
// };
// struct A
// {
// };
// struct B
// {
//     bool callA;
// };
// struct C
// {
//     int value;
// };
// 
// TEST_CASE("Event loop", "[EventLoop]")
// {
//     SECTION("Register and Dispatch")
//     {
//         fakeit::Mock<CallMeInterface> mock;
// 
// 
//         eul::event_loop<eul::events<8, A, B, C>> loop;
// 
//         Fake(Method(mock, a));
//         When(Method(mock, a)).AlwaysReturn();
//         loop.register_event<A>([&mock](const A&) { mock.get().a(); });
// 
//         loop.dispatch(A{});
//         Verify(Method(mock, a)).Exactly(1);
//         loop.dispatch(A{});
//         Verify(Method(mock, a)).Exactly(2);
//         loop.unregister<A>();
//         loop.dispatch(A{});
//         Verify(Method(mock, a)).Exactly(2);
// 
//         Fake(Method(mock, b));
//         loop.dispatch(B{1});
//         Verify(Method(mock, b)).Exactly(0);
// 
//         loop.register_event<B>([&mock](const B& b) {
//             if (b.callA)
//             {
//                 mock.get().a();
//             }
//             else
//             {
//                 mock.get().b();
//             }
//         });
// 
//         Fake(Method(mock, c));
// 
//         loop.register_event<C>([&mock](const C& c) { mock.get().c(c.value); });
// 
//         loop.dispatch(B{true});
//         Verify(Method(mock, a)).Exactly(3);
//         loop.dispatch(B{false});
//         Verify(Method(mock, b)).Exactly(1);
// 
//         loop.dispatch(C{123});
//         Verify(Method(mock, c).Using(123)).Once();
//     }
// }
