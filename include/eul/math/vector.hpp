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

namespace eul::math 
{

template <typename T, std::size_t N>
class vector
{
public:
    using self_type = vector<T, N>;
    
    template <typename ...Args>
    vector(Args&&...args) : data_{{std::forward<Args>(args)...}}
    {
    }

    self_type& operator+(const self_type& other)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            data_[i] += other[i]; 
        }

        return *this;
    }
   
    self_type& operator-(const self_type& other) 
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            data_[i] -= other[i];
        }
        return *this;
    }

    bool operator==(const self_type& other) const 
    {
        return data_ == other.data_;
    }

    const T& operator[](std::size_t i) const 
    {
        return data_[i];
    }

    T& operator[](std::size_t i) 
    {
        return data_[i];
    }

    T scalar_mul(const self_type& other)
    {
        T ans = 0;

        for (std::size_t i = 0; i < N; ++i)
        {
            ans += data_[i] * other[i];
        }
        return ans;
    }


private:
    std::array<T, N> data_;
};

} // namespace eul::math

