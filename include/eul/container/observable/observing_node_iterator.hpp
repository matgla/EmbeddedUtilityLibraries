#pragma once

#include <cstddef>

namespace eul
{
namespace container
{

template <typename T>
struct observing_node;

template <typename T>
class observing_node_iterator
{
public:
    observing_node_iterator(observing_node<T>* node, std::size_t position);

    observing_node_iterator<T>& operator++();

    bool operator!=(const observing_node_iterator<T>& it) const;
    observing_node<T>& operator*();

private:
    observing_node<T>* node_;
    std::size_t position_;
};


template <typename T>
observing_node_iterator<T>::observing_node_iterator(observing_node<T>* node,
                                                    std::size_t position)
    : node_(node), position_(position)
{
}

template <typename T>
observing_node_iterator<T>& observing_node_iterator<T>::operator++()
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
bool observing_node_iterator<T>::
    operator!=(const observing_node_iterator<T>& it) const
{
    return it.position_ != position_;
}

template <typename T>
observing_node<T>& observing_node_iterator<T>::operator*()
{
    return *node_;
}

} // namespace container
} // namespace eul
