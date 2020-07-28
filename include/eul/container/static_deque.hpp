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
#include <cmath>
#include <cstddef>
#include <initializer_list>

#include "eul/assert.hpp"
#include "eul/container/iterator/index_const_iterator.hpp"
#include "eul/container/iterator/index_iterator.hpp"

namespace eul::container
{

template <typename T, std::size_t Size>
class static_deque
{
public:
    using value_type     = T;
    using iterator       = container::iterator::index_iterator<static_deque<T, Size>>;
    using const_iterator = container::iterator::index_const_iterator<static_deque<T, Size>>;

    static_deque();
    static_deque(const std::initializer_list<T>& arguments);

    bool push_back(const T& data);
    bool push_front(const T& data);

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] constexpr std::size_t max_size() const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    iterator begin();
    [[nodiscard]] const_iterator begin() const;
    iterator end();
    [[nodiscard]] const_iterator end() const;

    void clear();

    T& front();
    [[nodiscard]] const T& front() const;
    T& back();
    [[nodiscard]] const T& back() const;

    bool pop_back();
    bool pop_front();

    [[nodiscard]] bool empty() const;

private:
    constexpr static void increment_index(std::size_t* index);
    constexpr static void decrement_index(std::size_t* index);

    bool full_{false};
    std::size_t head_{0};
    std::size_t tail_{0};
    std::array<T, Size> data_;
};

template <typename T, std::size_t Size>
static_deque<T, Size>::static_deque() = default;

template <typename T, std::size_t Size>
static_deque<T, Size>::static_deque(const std::initializer_list<T>& arguments)
{
    EUL_ASSERT_MSG(arguments.size() <= data_.max_size(), "Exceeded maximum arguments size");
    std::copy(arguments.begin(), arguments.end(), std::back_inserter(*this));
}

template <typename T, std::size_t Size>
bool static_deque<T, Size>::push_back(const T& data)
{
    if (full_)
    {
        return false;
    }

    data_.at(head_) = data;
    increment_index(&head_);
    full_ = tail_ == head_;
    return true;
}

template <typename T, std::size_t Size>
bool static_deque<T, Size>::push_front(const T& data)
{
    if (full_)
    {
        return false;
    }

    decrement_index(&tail_);

    data_.at(tail_) = data;
    full_        = tail_ == head_;
    return true;
}

template <typename T, std::size_t Size>
std::size_t static_deque<T, Size>::size() const
{
    if (full_)
    {
        return data_.max_size();
    }

    if (head_ >= tail_)
    {
        return head_ - tail_;
    }

    return data_.max_size() + head_ - tail_;
}

template <typename T, std::size_t Size>
constexpr std::size_t static_deque<T, Size>::max_size() const
{
    return Size;
}

template <typename T, std::size_t Size>
constexpr void static_deque<T, Size>::increment_index(std::size_t* index)
{
    ++(*index);
    *index = (*index) % Size;
}

template <typename T, std::size_t Size>
constexpr void static_deque<T, Size>::decrement_index(std::size_t* index)
{
    if ((*index) == 0)
    {
        (*index) = Size - 1;
        return;
    }
    --(*index);
}

template <typename T, std::size_t Size>
void static_deque<T, Size>::clear()
{
    full_ = false;
    head_ = 0;
    tail_ = 0;
}

template <typename T, std::size_t Size>
T& static_deque<T, Size>::operator[](std::size_t index)
{
    return data_.at((tail_ + index) % Size);
}

template <typename T, std::size_t Size>
const T& static_deque<T, Size>::operator[](std::size_t index) const
{

    return data_.at((tail_ + index) % Size);
}

template <typename T, std::size_t Size>
typename static_deque<T, Size>::iterator static_deque<T, Size>::begin()
{
    return iterator(*this, 0);
}

template <typename T, std::size_t Size>
typename static_deque<T, Size>::const_iterator static_deque<T, Size>::begin() const
{
    return const_iterator(*this, 0);
}

template <typename T, std::size_t Size>
typename static_deque<T, Size>::iterator static_deque<T, Size>::end()
{
    return iterator(*this, size());
}

template <typename T, std::size_t Size>
typename static_deque<T, Size>::const_iterator static_deque<T, Size>::end() const
{
    return const_iterator(*this, size());
}

template <typename T, std::size_t Size>
T& static_deque<T, Size>::front()
{
    return operator[](0);
}

template <typename T, std::size_t Size>
const T& static_deque<T, Size>::front() const
{
    return operator[](0);
}

template <typename T, std::size_t Size>
T& static_deque<T, Size>::back()
{
    return operator[](size() - 1);
}

template <typename T, std::size_t Size>
const T& static_deque<T, Size>::back() const
{
    return operator[](size() - 1);
}

template <typename T, std::size_t Size>
bool static_deque<T, Size>::pop_back()
{
    if (size() > 0)
    {
        decrement_index(&head_);
        if (full_)
        {
            full_ = false;
        }
        return true;
    }
    return false;
}

template <typename T, std::size_t Size>
bool static_deque<T, Size>::pop_front()
{
    if (size() > 0)
    {
        increment_index(&tail_);
        if (full_)
        {
            full_ = false;
        }
        return true;
    }
    return false;
}

template <typename T, std::size_t Size>
bool static_deque<T, Size>::empty() const
{
    return static_cast<bool>(size() <= 0);
}

} // namespace eul::container
