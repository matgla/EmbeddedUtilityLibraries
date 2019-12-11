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

#pragma once

#include <cstdint>

namespace eul
{
namespace memory
{
namespace pool
{
namespace details
{

class allocation_header
{
public:
    enum class State : uint8_t
    {
        Reserved = 0xAC,
        Free     = 0x00
    };

    allocation_header(const State state, const std::size_t size);
    State state() const;
    std::size_t size() const;

private:
    const State state_;
    const std::size_t size_;
};

// implementation

allocation_header::allocation_header(const State state, const std::size_t size)
    : state_(state)
    , size_(size)
{
}

allocation_header::State allocation_header::state() const
{
    return state_;
}

std::size_t allocation_header::size() const
{
    return size_;
}

} // namespace details
} // namespace pool
} // namespace memory
} // namespace eul
