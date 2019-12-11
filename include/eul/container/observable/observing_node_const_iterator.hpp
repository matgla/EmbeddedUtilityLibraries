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

namespace eul
{
namespace container
{

template <typename T>
class observing_node;

template <typename T>
class observing_node_const_iterator
{
public:
    observing_node_const_iterator(observing_node<T>* node,
                                  std::size_t position);

    const observing_node_const_iterator<T>& operator++();

    bool operator!=(const observing_node_const_iterator<T>& it) const;
    const observing_node<T>& operator*() const;

private:
    const observing_node<T>* node_;
    std::size_t position_;
};


template <typename T>
observing_node_const_iterator<T>::observing_node_const_iterator(
    observing_node<T>* node, std::size_t position)
    : node_(node), position_(position)
{
}

template <typename T>
const observing_node_const_iterator<T>& observing_node_const_iterator<T>::
    operator++()
{
    if (node_ == nullptr)
    {
        return *this;
    }

    node_ = node_->next();
    ++position_;
    return *this;
}

template <typename T>
bool observing_node_const_iterator<T>::
    operator!=(const observing_node_const_iterator<T>& it) const
{
    return it.position_ != position_;
}

template <typename T>
const observing_node<T>& observing_node_const_iterator<T>::operator*() const
{
    return *node_;
}

} // namespace container
} // namespace eul
