#pragma once

#include <array>
#include <cmath>
#include <cstddef>

namespace eul
{
namespace container
{

template <typename T, std::size_t Size>
class static_deque
{
public:
    static_deque();

    bool push_back(const T& data);
    bool push_front(const T& data);

    std::size_t size() const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

private:
    constexpr static void increment_index(std::size_t& index);
    constexpr static void decrement_index(std::size_t& index);

    bool full_;
    std::size_t head_;
    std::size_t tail_;
    std::array<T, Size> data_;
};

template <typename T, std::size_t Size>
static_deque<T, Size>::static_deque()
    : full_(false)
    , head_(0)
    , tail_(0)
{
}

template <typename T, std::size_t Size>
bool static_deque<T, Size>::push_back(const T& data)
{
    if (full_)
    {
        return false;
    }

    data_[head_] = data;
    increment_index(head_);
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

    decrement_index(tail_);

    data_[tail_] = data;
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
constexpr void static_deque<T, Size>::increment_index(std::size_t& index)
{
    ++index;
    index = index % Size;
}

template <typename T, std::size_t Size>
constexpr void static_deque<T, Size>::decrement_index(std::size_t& index)
{
    if (index == 0)
    {
        index = Size - 1;
        return;
    }
    --index;
}

template <typename T, std::size_t Size>
T& static_deque<T, Size>::operator[](std::size_t index)
{
    return data_[(tail_ + index) % Size];
}

template <typename T, std::size_t Size>
const T& static_deque<T, Size>::operator[](std::size_t index) const
{
    return data_[(tail_ + index) % Size];
}

} // namespace container
} // namespace eul