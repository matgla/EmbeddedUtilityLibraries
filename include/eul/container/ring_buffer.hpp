#pragma once

#include "eul/container/static_vector.hpp"

namespace eul
{
namespace container
{

template <typename T, std::size_t ContainerSize>
class ring_buffer
{
public:
    ring_buffer() : first_element_index_(0), last_element_index_(0)
    {
    }

    void push_back(const T& element)
    {
        if (last_element_index_ < data_.max_size())
        {
            data_[++last_element_index_];
        }
        else
        {
        }
    }

    void push_front(const T& element)
    {
    }

    std::size_t size() const
    {
        return last_element_index_ - first_element_index_;
    }

    T& pop_back()
    {
        return data_[last_element_index_--];
    }

private:
    std::size_t first_element_index_;
    std::size_t last_element_index_;
    static_vector<T, ContainerSize> data_;
};

} // namespace container
} // namespace eul