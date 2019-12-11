// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
