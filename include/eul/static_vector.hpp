#pragma once

#include <array>

namespace eul
{

template <typename Type, std::size_t BufferSize>
class static_vector
{

public:
    static_vector() : firstFreePosition_(0)
    {
    }

    void push_back(const Type& data)
    {
        if (firstFreePosition_ >= BufferSize)
        {
            return;
        }

        data_[firstFreePosition_] = data;
        ++firstFreePosition_;
    }

    std::size_t size() const
    {
        return firstFreePosition_;
    }

    constexpr std::size_t max_size() const
    {
        return BufferSize;
    }

    Type pop_back()
    {
        if (0 == firstFreePosition_)
        {
            return {};
        }
        --firstFreePosition_;
        return data_[firstFreePosition_];
    }

    Type get_last()
    {
        if (0 == size())
        {
            return {};
        }

        return data_[firstFreePosition_ - 1];
    }

    int find(int data) const
    {
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            if (data == data_[i])
            {
                return i;
            }
        }
        return -1;
    }

    void flush()
    {
        firstFreePosition_ = 0;
    }

    constexpr const Type* data() const noexcept
    {
        return data_.data();
    }

private:
    std::size_t firstFreePosition_;
    std::array<Type, BufferSize> data_;
};

} // namespace eul
