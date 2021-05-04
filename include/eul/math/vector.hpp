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

#pragma once 

#include <array>
#include <cstddef>

#include <iostream>

#include "eul/math/matrix.hpp"

namespace eul::math 
{

template <typename T, std::size_t N>
class vector : public matrix<T, N, 1>
{
public:
    vector() : matrix<T, N, 1>()
    {
    }

    vector(std::initializer_list<T> l) : matrix<T, N, 1>({l})
    {
    }

    using self_type = vector<T, N>;

    T dot(const self_type& other) const
    {
        T ans = 0;

        for (std::size_t i = 0; i < N; ++i)
        {
            std::cout << this->data_[0][i] << " * " << other[i] << std::endl;
            ans += this->data_[0][i] * other[i];
        }
        return ans;
    }

    T& operator[](std::size_t index) 
    {
        return this->data_[0][index];
    }

    const T& operator[](std::size_t index) const 
    {
        return this->data_[0][index];
    }

    bool operator==(const self_type& other) const 
    {
        return this->data_[0] == other[0];
    }

    constexpr static std::size_t size() 
    {
        return N;
    }
};

} // namespace eul::math

