// This file is part of EUL project.
// Copyright (C) 2021 Mateusz Stadnik
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

#include <catch2/catch_test_macros.hpp>

#include <chrono>

#include "eul/logger/logger.hpp"
#include "eul/logger/logger_factory.hpp"
#include "eul/time/i_time_provider.hpp"
#include "eul/logger/logger_stream_registry.hpp"
#include "eul/logger/logger_stream.hpp"

#include "TimeProviderStub.hpp"
#include "ExpectStream.hpp"

namespace eul::logger 
{

TEST_CASE("LoggerInfoPolicyShould", "[LOGGER_TESTS]")
{
    SECTION("Print info warning and error") 
    {
        ExpectStream stream;
        logger_stream_registry::get().register_stream(stream);
        TimeProviderStub time_provider;
        auto logger = logger_factory(time_provider)
            .create("LoggerTest", "InfoTest");

        stream.expect_none();
        logger.trace() << "Trace is printed";
        stream.expect_none();
        logger.debug() << "Debug is printed";
        stream.expect_none();

        constexpr std::chrono::hours time1{1000000};
        time_provider.set_time(time1);
        stream.expect("INF/InfoTest/LoggerTest: info prints octal 23224\n", time1);

        logger.info() << "info" << " prints octal " << eul::logger::oct << 9876;

        time_provider.set_time(std::chrono::milliseconds(0));
        stream.expect("WRN/InfoTest/LoggerTest: warning is printed out with hex 0xabcd\n", std::chrono::milliseconds{0});
        logger.warning() << "warning is printed out with hex 0x" << eul::logger::hex << 0xabcd;

        constexpr std::chrono::seconds time2{1000000};
        time_provider.set_time(time2);
        stream.expect("ERR/InfoTest/LoggerTest: Error is printed with 1234\n", time2);
        logger.error() << "Error" << " is printed with " << eul::logger::dec << 1234;
    }
}

} // namespace eul::logger 

