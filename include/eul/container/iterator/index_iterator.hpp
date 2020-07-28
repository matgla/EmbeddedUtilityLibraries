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

#include <cstddef>
#include <iterator>

namespace eul::container::iterator
{

template <typename ContainerType>
class index_iterator : public std::iterator<std::forward_iterator_tag, typename ContainerType::value_type>
{
    using Self = index_iterator<ContainerType>;

public:
    index_iterator(ContainerType& object, std::size_t index);
    ~index_iterator()                     = default;
    index_iterator(const index_iterator&) = default;
    index_iterator(index_iterator&&)       noexcept = default;
    index_iterator& operator=(index_iterator&&)  noexcept = default;
    index_iterator& operator=(const index_iterator&) = default;

    index_iterator operator++(int);
    index_iterator& operator++();
    bool operator==(const index_iterator& it) const;
    bool operator!=(const index_iterator& it) const;
    typename std::iterator_traits<Self>::value_type& operator*();
    typename std::iterator_traits<Self>::value_type* operator->();

private:
    ContainerType& object_;
    std::size_t index_;
};

template <typename ContainerType>
index_iterator<ContainerType>::index_iterator(ContainerType& object, std::size_t index)
    : object_(object)
    , index_(index)
{
}

template <typename ContainerType>
index_iterator<ContainerType> index_iterator<ContainerType>::operator++(int)
{
    ++index_;
    return index_iterator(object_, index_ - 1);
}

template <typename ContainerType>
index_iterator<ContainerType>& index_iterator<ContainerType>::operator++()
{
    ++index_;
    return *this;
}

template <typename ContainerType>
bool index_iterator<ContainerType>::operator==(const index_iterator<ContainerType>& it) const
{
    return this->index_ == it.index_;
}

template <typename ContainerType>
bool index_iterator<ContainerType>::operator!=(const index_iterator<ContainerType>& it) const
{
    return this->index_ != it.index_;
}

template <typename ContainerType>
typename std::iterator_traits<index_iterator<ContainerType>>::value_type& index_iterator<ContainerType>::
    operator*()
{
    return object_[index_];
}

template <typename ContainerType>
typename std::iterator_traits<index_iterator<ContainerType>>::value_type* index_iterator<ContainerType>::
    operator->()
{
    return &object_[index_];
}

} // namespace eul::container::iterator
