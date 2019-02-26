#pragma once

#include <cstddef>

namespace eul
{
namespace container
{
namespace iterator
{

template <typename ContainerType>
class index_iterator
{
public:
    // TODO: add iterator tag
    using value_type = typename ContainerType::value_type;

    index_iterator(ContainerType& container, std::size_t index);
    ~index_iterator()                     = default;
    index_iterator(const index_iterator&) = default;
    index_iterator(index_iterator&&)      = default;
    index_iterator& operator=(index_iterator&&) = default;
    index_iterator& operator=(const index_iterator&) = default;

    index_iterator operator++(int);
    index_iterator& operator++();
    bool operator==(const index_iterator& it) const;
    bool operator!=(const index_iterator& it) const;
    value_type& operator*();
    value_type* operator->();

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
typename index_iterator<ContainerType>::value_type& index_iterator<ContainerType>::operator*()
{
    return object_[index_];
}

template <typename ContainerType>
typename index_iterator<ContainerType>::value_type* index_iterator<ContainerType>::operator->()
{
    return &object_[index_];
}

} // namespace iterator
} // namespace container
} // namespace eul
