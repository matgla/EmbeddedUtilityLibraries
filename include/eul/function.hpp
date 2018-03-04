#pragma once

#include <cassert>
#include <cstdio>
#include <new>
#include <type_traits>
#include <utility>

namespace eul
{
template <class, std::size_t>
class function;

template <std::size_t Size, class ReturnType, class... Args>
class function<ReturnType(Args...), Size>
{
public:
    constexpr static std::size_t size = Size;

    using StorageType = typename std::aligned_storage<size, 8>::type;
    using This        = function<ReturnType(Args...), size>;

    function() noexcept
        : vtable_{}
    {
    }

    function(std::nullptr_t) noexcept
        : vtable_{}
    {
    }

    function(const function& other)
    {
        if (other)
        {
            other.copyTo(storage_, &vtable_);
        }
    }

    function(function&& other)
    {
        if (other)
        {
            other.moveTo(storage_, &vtable_);
        }
    }

    function(function& other)
    {
        if (other)
        {
            other.copyTo(storage_, &vtable_);
        }
    }

    template <class F>
    function(F&& f)
    {
        registerCallback(std::forward<F>(f));
    }

    ~function()
    {
        if (vtable_.exec)
        {
            vtable_.destructor(&storage_);
        }
    }


    function& operator=(const function& other)
    {
        if (vtable_.exec)
        {
            vtable_.destructor(&storage_);
        }
        other.copyTo(storage_, &vtable_);
        return *this;
    }

    function& operator=(function&& other)
    {
        if (vtable_.exec)
        {
            vtable_.destructor(&storage_);
        }
        other.moveTo(storage_, &vtable_);
        return *this;
    }

    function& operator=(std::nullptr_t)
    {
        if (vtable_.exec)
        {
            vtable_.destructor(&storage_);
        }
        vtable_.move       = nullptr;
        vtable_.copy       = nullptr;
        vtable_.destructor = nullptr;
        vtable_.exec       = nullptr;
        return *this;
    }

    template <class F>
    function& operator=(F&& f) noexcept
    {
        if (vtable_.exec)
        {
            vtable_.destructor(&storage_);
        }
        registerCallback(std::forward<F>(f));
        return *this;
    }

    void swap(function& other) noexcept
    {
        auto copy = function(*this);
        *this     = other;
        other     = copy;
    }

    explicit operator bool() const noexcept
    {
        return vtable_.exec != nullptr;
    }

    ReturnType operator()(Args... args)
    {
        assert(vtable_.exec != nullptr && "Function not initialized!");
        return vtable_.exec(&storage_, std::forward<Args>(args)...);
    }

    ReturnType operator()(Args... args) const
    {
        assert(vtable_.exec != nullptr && "Function not initialized!");
        return vtable_.exec(&storage_, std::forward<Args>(args)...);
    }


private:
    void copyTo(StorageType& newPlace, void* vtable) const
    {
        vtable_.copy(&storage_, &newPlace, vtable);
    }

    void moveTo(StorageType& newPlace, void* vtable) const
    {
        vtable_.move(&storage_, &newPlace, vtable);
    }
    struct VTable
    {
        VTable()
            : exec{nullptr}, destructor{nullptr}, copy{nullptr}, move{nullptr}
        {
        }
        using ExecutorType   = ReturnType (*)(void*, Args&&...);
        using DestructorType = void (*)(void*);
        using CopyType       = void (*)(const void*, void*, void* vtable);
        using MoveType       = void (*)(const void*, void*, void* vtable);

        ExecutorType exec;
        DestructorType destructor;
        CopyType copy;
        MoveType move;
    };

    VTable vtable_;

    template <typename FunctionType>
    static ReturnType execute(void* data, Args&&... args)
    {
        FunctionType& f = *static_cast<FunctionType*>(data);

        return f(std::forward<Args>(args)...);
    }

    template <class FunctionType>
    static void deleteCallback(void* function)
    {
        FunctionType& f = *static_cast<FunctionType*>(function);
        f.~FunctionType();
    }

    template <class FunctionType>
    static void copy(const void* data, void* place, void* vtable)
    {
        const FunctionType f = *static_cast<const FunctionType*>(data);
        VTable& vt           = *static_cast<VTable*>(vtable);
        new (place) FunctionType(f);
        vt.exec       = &execute<FunctionType>;
        vt.destructor = &deleteCallback<FunctionType>;
        vt.copy       = &copy<FunctionType>;
        vt.move       = &move<FunctionType>;
    }

    template <class FunctionType>
    static void move(const void* data, void* place, void* vtable)
    {
        const FunctionType& f = *static_cast<const FunctionType*>(data);
        VTable& vt            = *static_cast<VTable*>(vtable);
        new (place) FunctionType(std::move(f));
        vt.exec       = &execute<FunctionType>;
        vt.destructor = &deleteCallback<FunctionType>;
        vt.copy       = &copy<FunctionType>;
        vt.move       = &move<FunctionType>;
    }

    template <class FunctionType>
    void registerCallback(FunctionType&& function)
    {
        using DecayedFunctionType = typename std::decay<FunctionType>::type;
        static_assert(!std::is_same<DecayedFunctionType, This>::value, "Wrong function type declared");
        static_assert(sizeof(DecayedFunctionType) <= size, "Buffer overflow. Increase size parameter!");

        new (&storage_) DecayedFunctionType(std::forward<FunctionType>(function));

        vtable_.exec       = &execute<DecayedFunctionType>;
        vtable_.destructor = &deleteCallback<DecayedFunctionType>;
        vtable_.copy       = &copy<DecayedFunctionType>;
        vtable_.move       = &move<DecayedFunctionType>;
    }

    StorageType storage_;
};

} // namespace eul