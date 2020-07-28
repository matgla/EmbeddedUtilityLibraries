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

#include <string>
#include <type_traits>

#include <catch.hpp>
#include <utility>

#include "eul/mpl/types/bind_type.hpp"

namespace eul::mpl::types
{

TEST_CASE("BindType should", "[BindType]")
{
    SECTION("Bind value to type")
    {
        class Logger;
        class LoggerImplementation
        {
        public:
            explicit LoggerImplementation(std::string name) : name_(std::move(name))
            {
            }
            [[nodiscard]] const std::string& get_name() const { return name_; }
        private:
            std::string name_;
        };

        auto binded = bind_type<Logger>::to(LoggerImplementation("MyAwesomeLogger"));

        REQUIRE(binded.value.get_name() == "MyAwesomeLogger");
        using BindedType = decltype(binded);
        REQUIRE(std::is_same<LoggerImplementation, BindedType::ValueType>::value);
        REQUIRE(std::is_same<Logger, BindedType::KeyType>::value);
    }
}

} // namespace eul::mpl::types
