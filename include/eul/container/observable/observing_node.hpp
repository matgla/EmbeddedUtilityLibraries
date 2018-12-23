#pragma once

#include <utility>

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node_const_iterator.hpp"
#include "eul/container/observable/observing_node_iterator.hpp"

namespace eul
{
namespace container
{

template <typename T>
class observing_list;

template <typename T>
class observing_node
{
public:
    using iterator       = observing_node_iterator<T>;
    using const_iterator = observing_node_const_iterator<T>;
    using data_type      = T;
    template <typename... Args>
    observing_node(Args... args);
    ~observing_node();

    observing_node(const observing_node<T>& node) = delete;
    observing_node<T>& operator=(const observing_node<T>& node) = delete;

    observing_node(observing_node<T>&& node) = default;
    observing_node<T>& operator=(observing_node<T>&& node) = default;

    void reset();

    template <typename... Args>
    void reset(Args&&... args);

    const observing_node<T>* next() const;
    observing_node<T>* next();
    const observing_node<T>* prev() const;
    observing_node<T>* prev();

    void set_next(observing_node<T>* node);
    void set_prev(observing_node<T>* node);
    void set_prev(observing_list<observing_node<T>>* list);

    bool is_subscribed() const;

    void reset_list();

    T& data();
    const T& data() const;

protected:
    T data_;
    observing_node<T>* next_;
    observing_node<T>* prev_;
    observing_list<observing_node<T>>* list_;
};


template <typename T>
template <typename... Args>
observing_node<T>::observing_node(Args... args)
    : data_{args...}, next_(nullptr), prev_(nullptr), list_(nullptr)
{
}

template <typename T>
observing_node<T>::~observing_node()
{
    reset();
}

template <typename T>
void observing_node<T>::reset()
{
    if (prev_)
    {
        prev_->set_next(next_);
    }
    if (next_)
    {
        next_->set_prev(prev_);
    }
    if (list_)
    {
        list_->set_root(next_);
        if (next_)
        {
            next_->set_prev(list_);
        }
    }
    prev_ = nullptr;
    next_ = nullptr;
    list_ = nullptr;
}

template <typename T>
template <typename... Args>
void observing_node<T>::reset(Args&&... args)
{
    data_ = T{args...};
}

template <typename T>
const observing_node<T>* observing_node<T>::next() const
{
    return next_;
}

template <typename T>
observing_node<T>* observing_node<T>::next()
{
    return next_;
}

template <typename T>
const observing_node<T>* observing_node<T>::prev() const
{
    return prev_;
}

template <typename T>
observing_node<T>* observing_node<T>::prev()
{
    return prev_;
}

template <typename T>
void observing_node<T>::set_next(observing_node<T>* node)
{
    next_ = node;
}

template <typename T>
void observing_node<T>::set_prev(observing_node<T>* node)
{
    prev_ = node;
}

template <typename T>
void observing_node<T>::set_prev(observing_list<observing_node<T>>* list)
{
    list_ = list;
}

template <typename T>
bool observing_node<T>::is_subscribed() const
{
    return prev_ != nullptr || next_ != nullptr || list_ != nullptr;
}

template <typename T>
void observing_node<T>::reset_list()
{
    list_ = nullptr;
}

template <typename T>
T& observing_node<T>::data()
{
    return data_;
}

template <typename T>
const T& observing_node<T>::data() const
{
    return data_;
}


} // namespace container
} // namespace eul