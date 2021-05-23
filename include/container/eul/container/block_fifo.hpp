// This file is part of eul project.
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

#include <array>
#include <cstddef>

namespace eul::container 
{

namespace detail 
{

template <std::size_t bytes, typename T>
constexpr std::size_t calculate_size()
{
    if (bytes % sizeof(T) == 0) return bytes/sizeof(T);
    return (bytes/sizeof(T)) + 1;
}

} // namespace detail

template <std::size_t Bytes>
struct BlockFifo 
{
public:

    [[nodiscard]] 
    std::size_t size() const
    {
         
    }
private: 
    struct Position {
        std::size_t index;
        std::size_t size; 
    };
    Position first_;
    Position last_; 

    std::array<std::size_t, detail::calculate_size<Bytes, std::size_t>()> data_;
};

} // namespace eul::container

