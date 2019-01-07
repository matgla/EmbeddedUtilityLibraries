#pragma once

#include <array>

namespace eul
{
namespace container
{
template <typename Type, std::size_t BufferSize>
class static_vector
{
protected:
    using DataContainerType = std::array<Type, BufferSize>;

public:
    using iterator       = typename DataContainerType::iterator;
    using const_iterator = typename DataContainerType::const_iterator;
    using value_type     = Type;
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

    const Type& operator[](const std::size_t index) const
    {
        return data_[index];
    }


    Type& operator[](std::size_t index)
    {
        return data_[index];
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

    const_iterator begin() const
    {
        return data_.begin();
    }

    iterator begin()
    {
        return data_.begin();
    }

    const_iterator end() const
    {
        return data_.begin() + firstFreePosition_;
    }

    iterator end()
    {
        return data_.begin() + firstFreePosition_;
    }

private:
    std::size_t firstFreePosition_;
    DataContainerType data_;
};

} // namespace container
} // namespace eul
