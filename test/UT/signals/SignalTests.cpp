#include <catch.hpp>

#include "eul/signals/signal.hpp"
#include "eul/signals/slot.hpp"

namespace eul
{
namespace signals
{

TEST_CASE("SignalShould", "[SignalsTests]")
{
    SECTION("Emit")
    {
        using SignalType = eul::signals::signal<void(int)>;
        SignalType sut;

        int value1 = 0;
        SignalType::slot_t slot1([&value1] (int a) {
            value1 = a;
        });

        int value2 = 0;
        SignalType::slot_t slot2([&value2] (int a) {
            value2 = a;
        });
        sut.connect(slot1);
        sut.connect(slot2);

        REQUIRE(0 == value1);
        REQUIRE(0 == value2);

        sut.emit(15);
        REQUIRE(15 == value1);
        REQUIRE(15 == value2);

        sut.emit(-1);
        REQUIRE(-1 == value1);
        REQUIRE(-1 == value2);

    }

    SECTION("Deregister dead slot")
    {
        using SignalType = eul::signals::signal<void(int)>;
        SignalType sut;

        int value1 = 0;
        SignalType::slot_t slot1([&value1] (int a) {
            value1 = a;
        });

        int value2 = 0;
        {
            SignalType::slot_t slot2([&value2] (int a) {
                value2 = a;
            });
            sut.connect(slot1);
            sut.connect(slot2);

            REQUIRE(0 == value1);
            REQUIRE(0 == value2);

            sut.emit(15);
            REQUIRE(15 == value1);
            REQUIRE(15 == value2);
        }
        sut.emit(-1);
        REQUIRE(-1 == value1);
        REQUIRE(15 == value2);
    }

    SECTION("Disconnect slot")
    {
        using SignalType = eul::signals::signal<void(int)>;
        SignalType sut;

        int value1 = 0;
        SignalType::slot_t slot1([&value1] (int a) {
            value1 = a;
        });

        int value2 = 0;

        SignalType::slot_t slot2([&value2] (int a) {
            value2 = a;
        });
        sut.connect(slot1);
        sut.connect(slot2);

        REQUIRE(0 == value1);
        REQUIRE(0 == value2);

        sut.emit(15);
        REQUIRE(15 == value1);
        REQUIRE(15 == value2);

        slot2.disconnect();
        sut.emit(-1);
        REQUIRE(-1 == value1);
        REQUIRE(15 == value2);

        sut.connect(slot2);
        sut.emit(150);
        REQUIRE(150 == value1);
        REQUIRE(150 == value2);
    }
}

} // namespace signals
} // namespace eul
