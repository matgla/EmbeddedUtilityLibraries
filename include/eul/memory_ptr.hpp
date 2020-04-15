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

template <typename T>
class memory_ptr
{
public:
    constexpr memory_ptr(std::intptr_t address)
        : address_(address)
    {
    }

    operator volatile T*() const
    {
        return reinterpret_cast<T*>(address_);
    }

    volatile T* operator->() const
    {
        return reinterpret_cast<T*>(address_);
    }

    volatile T* operator->() const volatile
    {
        return reinterpret_cast<volatile T*>(address_);
    }

private:
    std::intptr_t address_;
};

} // namespace eul
