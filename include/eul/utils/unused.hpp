#pragma once

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

// clang-format off
template <typename... T>
constexpr void UNUSED(T.../*unused*/)
{
};

template <typename A>
constexpr void UNUSED1(A a)
{
    UNUSED(a);
}

template <typename A, typename B>
constexpr void UNUSED2(A a, B b)
{
    UNUSED(a, b);
}

template <typename A, typename B, typename C>
constexpr void UNUSED3(A a, B b, C c)
{
    UNUSED(a, b, c);
}

template <typename A, typename B, typename C, typename D>
constexpr void UNUSED4(A a, B b, C c, D d)
{
    UNUSED(a, b, c, d);
}

template <typename A, typename B, typename C, typename D, typename E>
constexpr void UNUSED5(A a, B b, C c, D d, E e)
{
    UNUSED(a, b, c, d, e);
}



// clang-format on
