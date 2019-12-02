#pragma once

#include <array>

#include "eul/assert.hpp"

namespace eul
{
namespace container
{
template <typename Type, std::size_t BufferSize>
class static_vector
{
protected:
    using DataContainerType = std::array<Type, BufferSize>;
    using self_type = static_vector<Type, BufferSize>;
public:
    using iterator       = typename DataContainerType::iterator;
    using const_iterator = typename DataContainerType::const_iterator;
    using value_type     = Type;

    static_vector()
        : firstFreePosition_(0)
        , data_()
    {
    }

    static_vector(const std::initializer_list<Type>& arguments)
        : firstFreePosition_(0)
        , data_()
    {
        std::copy(arguments.begin(), arguments.end(), std::back_inserter(*this));
    }

    template <std::size_t count>
    void assign(const Type& data)
    {
        static_assert(count <= BufferSize, "Try to assign more values than container size");

        clear();
        for (std::size_t i = 0; i < count; ++i)
        {
            push_back(data);
        }
    }

    template <std::size_t OtherContainerSize>
    static_vector<Type, BufferSize>& operator=(const static_vector<Type, OtherContainerSize>& other)
    {
        static_assert(OtherContainerSize <= BufferSize, "Container to be copied can't fit");
        clear();
        std::copy(other.begin(), other.end(), std::back_inserter(*this));
        return *this;
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

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (firstFreePosition_ >= BufferSize)
        {
            return;
        }

        new (&data_[firstFreePosition_]) Type(args...);
        ++firstFreePosition_;
    }

    void erase(iterator it)
    {
        if (it == end())
        {
            return;
        }
        while(it != end())
        {
            *(it) = *(it + 1);
            ++it;
        }
        --firstFreePosition_;
    }

    const Type& operator[](const std::size_t index) const
    {
        return data_[index];
    }

    Type& operator[](const std::size_t index)
    {
        if (index + 1 > firstFreePosition_)
        {
            firstFreePosition_ = index + 1;
        }
        return data_[index];
    }

    template <std::size_t index>
    Type& at()
    {
        static_assert(index < BufferSize, "Trying to access element outside vector");
        return data_[index];
    }

    template <std::size_t index>
    const Type& at() const
    {
        static_assert(index < BufferSize, "Trying to access element outside vector");
        return data_[index];
    }

    std::size_t size() const
    {
        return firstFreePosition_;
    }

    constexpr static std::size_t max_size()
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

    Type& back()
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[firstFreePosition_ - 1];
    }

    Type& front()
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[0];
    }

    const Type& back() const
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[firstFreePosition_ - 1];
    }

    const Type& front() const
    {
        EUL_ASSERT_MSG(size() != 0, "Vector is empty!");

        return data_[0];
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

    void clear()
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

    bool empty() const
    {
        return size() == 0;
    }

    bool operator==(const self_type& other) const
    {
        if (other.size() != size())
        {
            return false;
        }

        for (std::size_t i = 0; i < size(); ++i)
        {
            if ((*this)[i] != other[i])
            {
                return false;
            }
        }
        return true;
    }
private:
    std::size_t firstFreePosition_;
    DataContainerType data_;
};

} // namespace container
} // namespace eul
