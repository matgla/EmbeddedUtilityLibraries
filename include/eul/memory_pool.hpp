#pragma once

#include <array>
#include <type_traits>

#include <string>
#include <sstream>

#include "eul/assert.hpp"

namespace eul
{
    
template<typename Type, typename PoolType>
struct pool_unique_ptr
{
    using SizeType = typename PoolType::SizeType;
    
    pool_unique_ptr(Type* ptr, PoolType& pool, SizeType positionInBuffer) : ptr_(ptr), pool_(pool), positionInBuffer_(positionInBuffer)
    {
    }
    
    ~pool_unique_ptr()
    {
        ptr_->~Type();
        pool_.deallocate(*this);
    }
    
    Type* operator->() const noexcept
    {
        return ptr_;
    }
    
    typename std::add_lvalue_reference<Type>::type operator*() const
    {
        return ptr_;
    }
    
    bool operator==(nullptr_t) const
    {
        return ptr_ == nullptr;
    }   
    
    bool operator!=(nullptr_t) const
    {
        return ptr_ != nullptr;
    }   
    
    void reset()
    {
        if (!ptr_) 
        { 
            return;
        }
        
        ptr_->~Type();
        pool_.deallocate(*this);
        
        ptr_ = nullptr;
    }
    
    const SizeType position() const
    {
        return positionInBuffer_;
    }
    
    Type* ptr_;
    PoolType& pool_;
    SizeType positionInBuffer_;
};
    
template<typename Type, typename PoolType>
pool_unique_ptr<Type, PoolType> make_pool_unique_ptr(Type* ptr, PoolType& pool, typename PoolType::SizeType positionInBuffer)
{
    return pool_unique_ptr(ptr, pool, positionInBuffer);
}
    
template<typename SizeType>
struct AllocationInfo
{
    enum class State : uint8_t
    {
        Reserved = 0xAC,
        Free = 0x00
    };
    
    State state;
    SizeType size;
};

template <typename TSizeType, TSizeType Size = 128>
struct MemoryPool
{
    using Storage = std::aligned_storage<sizeof(std::max_align_t), alignof(std::max_align_t)>::type;
    using SizeType = TSizeType;


    MemoryPool() : start_(0), current_(0), end_(0) 
    {
    }
    
    template <typename T>
    constexpr static T ceilingDivision(T a, T b)
    {
        return a / b + (a % b != 0);
    }
    
    constexpr static int getAllocationHeaderSize()
    {
        return ceilingDivision(sizeof(AllocationInfo<SizeType>), sizeof(std::max_align_t));
    }

    template <typename T, typename... Args>
    pool_unique_ptr<T, MemoryPool<TSizeType, Size>> allocate(Args&&... args)
    {
        constexpr auto allocationSize = ceilingDivision(sizeof(T), sizeof(std::max_align_t)) + getAllocationHeaderSize();
        static_assert(allocationSize <= Size, "Not enough space in buffer");
        const auto freeSpace = (data_.size() - current_);

        if (allocationSize > freeSpace)
        {
            return pool_unique_ptr<T, MemoryPool<TSizeType, Size>>(nullptr, *this, 0);
        }
        current_ = end_;
        AllocationInfo<SizeType>* allocationHeader = new(&data_[current_]) AllocationInfo<SizeType>;
        allocationHeader->state = AllocationInfo<SizeType>::State::Reserved;
        allocationHeader->size = sizeof(T) / sizeof(std::max_align_t) + (sizeof(T) % sizeof(std::max_align_t) != 0);
        SizeType headerPositionInBuffer = current_;
        current_ = end_;
        current_ += getAllocationHeaderSize();
        end_ = current_ + allocationHeader->size;
        auto* object = new (&data_[current_]) T(std::forward<Args>(args)...);
        return make_pool_unique_ptr(object, *this, headerPositionInBuffer);
    }
    
    template <typename T>
    void deallocate(const pool_unique_ptr<T, MemoryPool<TSizeType, Size>>& data)
    {
        AllocationInfo<SizeType>* header = reinterpret_cast<AllocationInfo<SizeType>*>(&data_[data.position()]);
    }
    
    std::string draw() const 
    {
        std::stringstream ss;
        ss << "[";
        bool endMemory = data_.size() == 0;
        while (!endMemory)
        {
            AllocationInfo<SizeType>* header = reinterpret_cast<AllocationInfo<SizeType>*>(&data_[start_]);
        }
    }
    
    int start_;
    int current_;
    int end_;
    std::array<Storage, Size/sizeof(std::max_align_t)> data_;
};

} // namespace eul
