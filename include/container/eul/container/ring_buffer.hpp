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

#include "eul/container/static_vector.hpp"

namespace eul::container
{

template <typename T, std::size_t ContainerSize>
class ring_buffer
{
public:

    T& push(const T& element)
    {
        data_[head_] = element;
        auto& new_element = data_[head_];

        if (full_)
        {
            increment_index(&tail_);
        }

        increment_index(&head_);
        full_ = tail_ == head_;
        return new_element;
    }

    [[nodiscard]]
    std::size_t size() const
    {
        if (full_)
        {
            return ContainerSize;
        }

        if (head_ >= tail_)
        {
            return head_ - tail_;
        }

        return data_.max_size() + head_ - tail_;
    }

    T& pop()
    {
        std::size_t old_tail = tail_;
        increment_index(&tail_);
        full_ = false;
        return data_[old_tail];
    }

    T& front()
    {
        return data_[tail_];
    }

    [[nodiscard]] const T& front() const
    {
        return data_[tail_];
    }

    [[nodiscard]]
    bool full() const
    {
        return full_;
    }

    [[nodiscard]]
    bool empty() const
    {
        return size() == 0;
    }

private:
    void increment_index(std::size_t* index) const
    {
        ++(*index);
        (*index) = (*index) % ContainerSize;
    }

    std::size_t tail_{0};
    std::size_t head_{0};
    bool full_{false};
    static_vector<T, ContainerSize> data_;
};

} // namespace eul::container
