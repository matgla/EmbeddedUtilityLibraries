#pragma once

#include <cstddef>
#include <optional>

#include "eul/observer/observing_node.hpp"
#include "eul/observer/observing_node_const_iterator.hpp"
#include "eul/observer/observing_node_iterator.hpp"

namespace eul
{
namespace observer
{

template <typename T>
class observing_list
{
public:
    observing_list();

    bool push_back(observing_node<T>& node);
    bool insert_after(observing_node<T>& prev, observing_node<T>& node);
    bool insert_before(observing_node<T>& next, observing_node<T>& node);

    std::optional<T*> at(const std::size_t index);
    observing_node<T>* find(observing_node<T>* node);

    observing_node_iterator<T> begin();
    const observing_node_iterator<T> begin() const;

    observing_node_iterator<T> end();
    const observing_node_iterator<T> end() const;

    void set_root(observing_node<T>* root);

    std::size_t size() const;

    bool is_observed(observing_node<T>* node);


private:
    observing_node<T>* get_end();

    const observing_node<T>* get_end() const;

    void link(observing_node<T>& prev, observing_node<T>& node);
    void link(observing_node<T>& node);

    observing_node<T>* root_;
};

template <typename T>
observing_list<T>::observing_list() : root_{nullptr}
{
}

template <typename T>
bool observing_list<T>::push_back(observing_node<T>& node)
{
    if (is_observed(&node))
    {
        return false;
    }
    node.reset();

    if (!root_)
    {
        link(node);
        return true;
    }

    link(*get_end(), node);
    return true;
}

template <typename T>
bool observing_list<T>::insert_after(observing_node<T>& prev,
                                     observing_node<T>& node)
{
    auto* current = find(&prev);
    if (!current)
    {
        return false;
    }

    node.reset();
    link(prev, node);

    return true;
}

template <typename T>
bool observing_list<T>::insert_before(observing_node<T>& next,
                                      observing_node<T>& node)
{
    auto* current = find(&next);
    if (!current)
    {
        return false;
    }

    node.reset();
    if (current == root_)
    {
        link(node);
        return true;
    }

    link(*current->prev(), node);

    return true;
}

template <typename T>
std::optional<T*> observing_list<T>::at(const std::size_t index)
{
    if (!root_)
    {
        return {};
    }

    observing_node<T>* node = root_;
    for (std::size_t i = 0; i < index; ++i)
    {
        if (!node->next())
        {
            return {};
        }

        node = node->next();
    }
    return &node->data();
}

template <typename T>
observing_node<T>* observing_list<T>::find(observing_node<T>* node)
{
    if (!root_)
    {
        return nullptr;
    }

    observing_node<T>* current = root_;
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

template <typename T>
observing_node_iterator<T> observing_list<T>::begin()
{
    return observing_node_iterator<T>(root_, 0);
}

template <typename T>
const observing_node_iterator<T> observing_list<T>::begin() const
{
    return observing_node_const_iterator<T>(*root_, 0);
}

template <typename T>
observing_node_iterator<T> observing_list<T>::end()
{
    return observing_node_iterator<T>(nullptr, size());
}

template <typename T>
const observing_node_iterator<T> observing_list<T>::end() const
{
    return observing_node_const_iterator<T>(nullptr, size());
}


template <typename T>
std::size_t observing_list<T>::size() const
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

template <typename T>
void observing_list<T>::set_root(observing_node<T>* root)
{
    root_ = root;
}

template <typename T>
bool observing_list<T>::is_observed(observing_node<T>* node)
{
    return find(node) != nullptr;
}

template <typename T>
observing_node<T>* observing_list<T>::get_end()
{
    if (!root_)
    {
        return nullptr;
    }

    observing_node<T>* current = root_;
    while (current->next() != nullptr)
    {
        current = current->next();
    }
    return current;
}

template <typename T>
const observing_node<T>* observing_list<T>::get_end() const
{
    if (!root_)
    {
        return nullptr;
    }

    observing_node<T>* current = root_;
    while (current->next() != nullptr)
    {
        current = current->next();
    }
    return current;
}

template <typename T>
void observing_list<T>::link(observing_node<T>& prev, observing_node<T>& node)
{
    node.set_next(prev.next());

    if (prev.next())
    {
        prev.next()->set_prev(&node);
    }

    prev.set_next(&node);
    node.set_prev(&prev);
}

template <typename T>
void observing_list<T>::link(observing_node<T>& node)
{
    if (root_)
    {
        root_->reset_list();
        root_->set_prev(&node);
    }

    node.set_next(root_);
    node.set_prev(this);
    root_ = &node;
}

} // namespace observer
} // namespace eul