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

#include "eul/container/observable/observing_node.hpp"
#include "eul/container/observable/observing_node_const_iterator.hpp"
#include "eul/container/observable/observing_node_iterator.hpp"

namespace eul::container
{

template <typename NodeType>
class observing_list
{
public:
    observing_list();
    ~observing_list();

    observing_list(const observing_list& other) = delete;
    observing_list(observing_list&& other)      = delete;

    observing_list& operator=(const observing_list& other) = delete;
    observing_list& operator=(observing_list&& other)      = delete;

    bool push_back(NodeType& node);
    bool push_front(NodeType& node);
    bool insert_after(NodeType& prev, NodeType& node);
    bool insert_before(NodeType* next, NodeType& node);

    typename NodeType::data_type* at(std::size_t index);
    NodeType* find(const NodeType* node);
    const NodeType* find(const NodeType* node) const;

    typename NodeType::iterator begin();
    [[nodiscard]] typename NodeType::const_iterator begin() const;

    typename NodeType::iterator end();
    [[nodiscard]] typename NodeType::const_iterator end() const;

    void set_root(NodeType* root);

    [[nodiscard]] std::size_t size() const;

    bool is_observed(NodeType* node);

    void erase(const NodeType& node);

    void clear();

    void swap(NodeType* old, NodeType* node) noexcept;

private:
    NodeType* get_end();

    [[nodiscard]] const NodeType* get_end() const;

    void link(NodeType& prev, NodeType& node);
    void link(NodeType& node);

    NodeType* root_{nullptr};
};

template <typename NodeType>
observing_list<NodeType>::observing_list()

    = default;

template <typename NodeType>
observing_list<NodeType>::~observing_list()
{
    clear();
}

template <typename NodeType>
bool observing_list<NodeType>::push_back(NodeType& node)
{
    if (node.get_list() != this)
    {
        node.reset();
    }
    if (is_observed(&node))
    {
        return false;
    }

    if (!root_)
    {
        link(node);
        return true;
    }

    link(*get_end(), node);
    return true;
}

template <typename NodeType>
bool observing_list<NodeType>::push_front(NodeType& node)
{
    return insert_before(root_, node);
}

template <typename NodeType>
bool observing_list<NodeType>::insert_after(NodeType& prev, NodeType& node)
{
    if (find(&node) != nullptr)
    {
        return false;
    }

    if (!find(&prev))
    {
        return false;
    }

    if (node.get_list() != this)
    {
        node.reset();
    }

    link(prev, node);

    return true;
}

template <typename NodeType>
bool observing_list<NodeType>::insert_before(NodeType* next, NodeType& node)
{
    if (find(&node) != nullptr)
    {
        return false;
    }
    if (root_ == nullptr)
    {
        link(node);
    }

    auto* current = find(next);
    if (!current)
    {
        return false;
    }

    if (node.get_list() != this)
    {
        node.reset();
    }
    if (current == root_)
    {
        link(node);
        return true;
    }

    link(*current->prev(), node);

    return true;
}

template <typename NodeType>
typename NodeType::data_type* observing_list<NodeType>::at(const std::size_t index)
{
    if (!root_)
    {
        return nullptr;
    }

    NodeType* node = root_;
    for (std::size_t i = 0; i < index; ++i)
    {
        if (!node->next())
        {
            return nullptr;
        }

        node = node->next();
    }
    return &node->data();
}

template <typename NodeType>
NodeType* observing_list<NodeType>::find(const NodeType* node)
{
    if (!root_)
    {
        return nullptr;
    }

    NodeType* current = root_;
    while (current != nullptr)
    {
        if (current == node)
        {
            return current;
        }

        current = current->next();
    }
    return nullptr;
}

template <typename NodeType>
const NodeType* observing_list<NodeType>::find(const NodeType* node) const
{
    if (!root_)
    {
        return nullptr;
    }

    NodeType* current = root_;
    while (current != nullptr)
    {
        if (current == node)
        {
            return current;
        }

        current = current->next();
    }
    return nullptr;
}

template <typename NodeType>
typename NodeType::iterator observing_list<NodeType>::begin()
{
    return observing_node_iterator<typename NodeType::data_type>(root_, 0);
}

template <typename NodeType>
typename NodeType::const_iterator observing_list<NodeType>::begin() const
{
    return observing_node_const_iterator<typename NodeType::data_type>(root_, 0);
}

template <typename NodeType>
typename NodeType::iterator observing_list<NodeType>::end()
{
    return observing_node_iterator<typename NodeType::data_type>(nullptr, size());
}

template <typename NodeType>
typename NodeType::const_iterator observing_list<NodeType>::end() const
{
    return observing_node_const_iterator<typename NodeType::data_type>(nullptr, size());
}


template <typename NodeType>
std::size_t observing_list<NodeType>::size() const
{
    if (!root_)
    {
        return 0;
    }

    std::size_t i = 1;
    auto* node    = root_;
    while (node->next())
    {
        ++i;
        node = node->next();
    }
    return i;
}

template <typename NodeType>
void observing_list<NodeType>::set_root(NodeType* root)
{
    root_ = root;
}

template <typename NodeType>
bool observing_list<NodeType>::is_observed(NodeType* node)
{
    return find(node) != nullptr;
}

template <typename NodeType>
void observing_list<NodeType>::erase(const NodeType& node)
{
    auto* nodeInList = find(&node);
    if (nodeInList != nullptr)
    {
        nodeInList->reset();
    }
}

template <typename NodeType>
NodeType* observing_list<NodeType>::get_end()
{
    if (!root_)
    {
        return nullptr;
    }

    NodeType* current = root_;
    while (current->next() != nullptr)
    {
        current = current->next();
    }
    return current;
}

template <typename NodeType>
const NodeType* observing_list<NodeType>::get_end() const
{
    if (!root_)
    {
        return nullptr;
    }

    NodeType* current = root_;
    while (current->next() != nullptr)
    {
        current = current->next();
    }
    return current;
}

template <typename NodeType>
void observing_list<NodeType>::link(NodeType& prev, NodeType& node)
{
    node.set_list(this);
    node.set_next(prev.next());

    if (prev.next())
    {
        prev.next()->set_prev(&node);
    }

    prev.set_next(&node);
    node.set_prev(&prev);
}

template <typename NodeType>
void observing_list<NodeType>::link(NodeType& node)
{
    if (root_)
    {
        root_->set_prev(&node);
    }

    node.set_next(root_);
    node.set_prev(this);
#ifdef __GNUC__
#ifndef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdangling-pointer=0"
#endif // __clang__
#endif // _GNUC_
    root_ = &node;
#ifdef __GNUC__
#ifndef __clang__
#pragma GCC diagnostic pop
#endif // __clang__
#endif // _GNUC_
}

template <typename NodeType>
void observing_list<NodeType>::clear()
{
    auto* current = root_;
    while (current)
    {
        auto* next = current->next();

        current->reset();
        current = next;
    }
    root_ = nullptr;
}

template <typename NodeType>
void observing_list<NodeType>::swap(NodeType* old, NodeType* node) noexcept
{
    if (root_ == old)
    {
        root_ = node;
    }
    else
    {
        old->prev()->set_next(node);
    }
}


} // namespace eul::container
