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
#include <algorithm>
#include <cstddef>

namespace eul::math 
{

template <typename T, std::size_t Columns, std::size_t Rows>
class matrix 
{
public:
    using self_type = matrix<T, Columns, Rows>;
   
    constexpr matrix()
    {
        for (auto& row : data_)
        {
            row.fill(0);
        }
    }

    constexpr matrix(std::initializer_list<std::initializer_list<T>> l) 
    {
        std::size_t i = 0;
        for (auto& row : l)
        {
            std::ranges::copy(row.begin(), row.end(), data_.at(i).begin());
            ++i;
        }
    }

    self_type operator+(self_type other) const
    {
        for (std::size_t i = 0; i < Rows; ++i)
        {
            for (std::size_t j = 0; j < Columns; ++j)
            {
                other.at(i).at(j) += data_.at(i).at(j); 
            }
        }

        return other;
    }
 
    self_type& operator+=(self_type other) 
    {
        for (std::size_t i = 0; i < Rows; ++i)
        {
            for (std::size_t j = 0; j < Columns; ++j)
            {
                data_.at(i).at(j) += other.at(i).at(j); 
            }
        }
        return *this;
    }

    self_type operator-(self_type other) const
    {
        for (std::size_t i = 0; i < Rows; ++i)
        {
            for (std::size_t j = 0; j < Columns; ++j)
            {
                other.at(i).at(j) = data_.at(i).at(j) - other.at(i).at(j); 
            }
        }

        return other;
    }
 
    self_type& operator-=(self_type other) 
    {
        for (std::size_t i = 0; i < Rows; ++i)
        {
            for (std::size_t j = 0; j < Columns; ++j)
            {
                data_.at(i).at(j) -= other.at(i).at(j); 
            }
        }
        return *this;
    }
 
    self_type operator*(T mul) const
    {
        self_type other;
        for (std::size_t i = 0; i < Rows; ++i)
        {
            for (std::size_t j = 0; j < Columns; ++j)
            {
                other.at(i).at(j) = data_.at(i).at(j) * mul; 
            }
        }

        return other;
    }
 
    self_type& operator*=(T mul) 
    {
        for (std::size_t i = 0; i < Rows; ++i)
        {
            for (std::size_t j = 0; j < Columns; ++j)
            {
                data_.at(i).at(j) *= mul; 
            }
        }
        return *this;
    }

    template <std::size_t OtherColumns>
    matrix<T, OtherColumns, Rows> operator*(const matrix<T, OtherColumns, Columns>& other) const
    {
        matrix<T, OtherColumns, Rows> answer;

        for (std::size_t i = 0; i < Rows; ++i)
        {
            for (std::size_t j = 0; j < OtherColumns; ++j)
            {
                T part = 0; 
                for (std::size_t x = 0; x < Columns; ++x)
                {
                    part += data_.at(i).at(x) * other.at(x).at(j);
                }
                answer.at(i).at(j) = part;
            }
        }

        return answer;
    }
 
    
    bool operator==(const self_type& other) const = default;

    const std::array<T, Columns>& operator[](std::size_t i) const 
    {
        return data_.at(i);
    }

    std::array<T, Columns>& operator[](std::size_t i) 
    {
        return data_.at(i);
    }

    [[nodiscard]] const std::array<T, Columns>& at(std::size_t i) const 
    {
        return data_.at(i);
    }

    std::array<T, Columns>& at(std::size_t i) 
    {
        return data_.at(i);
    }

    constexpr static std::size_t rows() 
    {
        return Rows;
    }

    constexpr static std::size_t columns() 
    {
        return Columns;
    }

private:
    std::array<std::array<T, Columns>, Rows> data_;
};

} // namespace eul::math

