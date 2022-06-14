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

#include <array>

#include "eul/utils/assert.hpp"

namespace eul::container
{

template <typename Type, std::size_t BufferSize>
class static_vector
{
protected:
    using DataContainerType = std::array<Type, BufferSize>;
    using self_type = static_vector<Type, BufferSize>;
public:
    using iterator       = typename DataContainerType::iterator;
    using const_iterator = typename DataContainerType::const_iterator;
    using value_type     = Type;

    static_vector()
        : data_()
    {
    }

    explicit static_vector(const std::initializer_list<Type>& arguments)
        : data_()
    {
        std::copy(arguments.begin(), arguments.end(), std::back_inserter(*this));
    }

    template <std::size_t count>
    void assign(const Type& data)
    {
        static_assert(count <= BufferSize, "Try to assign more values than container size");

        clear();
        for (std::size_t i = 0; i < count; ++i)
        {
            push_back(data);
        }
    }

    template <std::size_t OtherContainerSize>
    static_vector<Type, BufferSize>& operator=(const static_vector<Type, OtherContainerSize>& other)
    {
        static_assert(OtherContainerSize <= BufferSize, "Container to be copied can't fit");
        clear();
        std::copy(other.begin(), other.end(), std::back_inserter(*this));
        return *this;
    }

    void push_back(const Type& data)
    {
        if (firstFreePosition_ >= BufferSize)
        {
            return;
        }

        data_[firstFreePosition_] = data;
        ++firstFreePosition_;
    }

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (firstFreePosition_ >= BufferSize)
        {
            return;
        }

        new (&data_[firstFreePosition_]) Type(args...);
        ++firstFreePosition_;
    }

    void erase(iterator it)
    {
        if (it == end())
        {
            return;
        }
        while(it != end() && (it + 1) != end())
        {
            *(it) = *(it + 1);
            ++it;
        }
        --firstFreePosition_;
    }

    const Type& operator[](const std::size_t index) const
    {
        return data_[index];
    }

    Type& operator[](const std::size_t index)
    {
        if (index + 1 > firstFreePosition_)
        {
            firstFreePosition_ = index + 1;
        }
        return data_[index];
    }

    template <std::size_t index>
    Type& at()
    {
        static_assert(index < BufferSize, "Trying to access element outside vector");
        return data_[index];
    }

    template <std::size_t index>
    [[nodiscard]] const Type& at() const
    {
        static_assert(index < BufferSize, "Trying to access element outside vector");
        return data_[index];
    }

    [[nodiscard]] std::size_t size() const
    {
        return firstFreePosition_;
    }

    constexpr static std::size_t max_size()
    {
        return BufferSize;
    }

    Type pop_back()
    {
        if (0 == firstFreePosition_)
        {
            return {};
        }
        --firstFreePosition_;
        return data_[firstFreePosition_];
    }

    Type& back()
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[firstFreePosition_ - 1];
    }

    Type& front()
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[0];
    }

    [[nodiscard]] const Type& back() const
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[firstFreePosition_ - 1];
    }

    [[nodiscard]] const Type& front() const
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[0];
    }

    [[nodiscard]] int find(int data) const
    {
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            if (data == data_[i])
            {
                return i;
            }
        }

        return -1;
    }

    void clear()
    {
        firstFreePosition_ = 0;
    }

    [[nodiscard]] constexpr const Type* data() const noexcept
    {
        return data_.data();
    }

    [[nodiscard]] const_iterator begin() const
    {
        return data_.begin();
    }

    iterator begin()
    {
        return data_.begin();
    }

    [[nodiscard]] const_iterator end() const
    {
        return data_.begin() + firstFreePosition_;
    }

    iterator end()
    {
        return data_.begin() + firstFreePosition_;
    }

    [[nodiscard]] bool empty() const
    {
        return size() == 0;
    }

    bool operator==(const self_type& other) const
    {
        if (other.size() != size())
        {
            return false;
        }

        for (std::size_t i = 0; i < size(); ++i)
        {
            if ((*this)[i] != other[i])
            {
                return false;
            }
        }
        return true;
    }
private:
    std::size_t firstFreePosition_{0};
    DataContainerType data_;
};

} // namespace eul::container
