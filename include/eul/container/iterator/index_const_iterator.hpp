#pragma once

#include <cstddef>

namespace eul
{
namespace container
{
namespace iterator
{

template <typename ContainerType>
class index_const_iterator
{
public:
    // TODO: add iterator tag
    using value_type = typename ContainerType::value_type;

    index_const_iterator(const ContainerType& container, std::size_t index);
    ~index_const_iterator()                           = default;
    index_const_iterator(const index_const_iterator&) = default;
    index_const_iterator(index_const_iterator&&)      = default;
    index_const_iterator& operator=(index_const_iterator&&) = default;
    index_const_iterator& operator=(const index_const_iterator&) = default;

    index_const_iterator operator++(int);
    index_const_iterator& operator++();
    bool operator==(const index_const_iterator& it) const;
    bool operator!=(const index_const_iterator& it) const;
    const value_type& operator*() const;
    const value_type* operator->() const;

private:
    const ContainerType& object_;
    std::size_t index_;
};

template <typename ContainerType>
index_const_iterator<ContainerType>::index_const_iterator(const ContainerType& object, std::size_t index)
    : object_(object)
    , index_(index)
{
}

template <typename ContainerType>
index_const_iterator<ContainerType> index_const_iterator<ContainerType>::operator++(int)
{
    ++index_;
    return index_const_iterator(object_, index_ - 1);
}

template <typename ContainerType>
index_const_iterator<ContainerType>& index_const_iterator<ContainerType>::operator++()
{
    ++index_;
    return *this;
}

template <typename ContainerType>
bool index_const_iterator<ContainerType>::operator==(const index_const_iterator<ContainerType>& it) const
{
    return this->index_ == it.index_;
}

template <typename ContainerType>
bool index_const_iterator<ContainerType>::operator!=(const index_const_iterator<ContainerType>& it) const
{
    return this->index_ != it.index_;
}

template <typename ContainerType>
const typename index_const_iterator<ContainerType>::value_type& index_const_iterator<ContainerType>::
    operator*() const
{
    return object_[index_];
}

template <typename ContainerType>
const typename index_const_iterator<ContainerType>::value_type* index_const_iterator<ContainerType>::
    operator->() const
{
    return &object_[index_];
}

} // namespace iterator
} // namespace container
} // namespace eul
