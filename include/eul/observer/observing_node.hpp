#pragma once

#include <utility>

namespace eul
{
namespace observer
{

template <typename T>
class observing_list;

template <typename T>
class observing_node
{
public:
    template <typename... Args>
    observing_node(Args... args);
    ~observing_node();

    void reset();

    const observing_node<T>* next() const;
    observing_node<T>* next();
    const observing_node<T>* prev() const;
    observing_node<T>* prev();

    void set_next(observing_node<T>* node);
    void set_prev(observing_node<T>* node);
    void set_prev(observing_list<T>* list);

    void reset_list();

    T& data();

private:
    T data_;
    observing_node<T>* next_;
    observing_node<T>* prev_;
    observing_list<T>* list_;
};


template <typename T>
template <typename... Args>
observing_node<T>::observing_node(Args... args)
    : data_(std::forward<Args>(args)...), next_(nullptr), prev_(nullptr),
      list_(nullptr)
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
void observing_node<T>::set_prev(observing_list<T>* list)
{
    list_ = list;
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

} // namespace observer
} // namespace eul