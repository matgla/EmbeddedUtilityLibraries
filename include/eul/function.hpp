#pragma once

#include <cassert>
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

    using storage_type = typename std::aligned_storage<size, 8>::type;
    using this_type    = function<ReturnType(Args...), size>;

    function() noexcept
        : vtable_{}
    {
    }

    explicit function(std::nullptr_t) noexcept
        : vtable_{}
    {
    }

    function(const function& other)
    {
        if (other)
        {
            other.copy_to(storage_, &vtable_);
        }
    }

    function(function&& other) noexcept
    {
        if (other)
        {
            other.move_to(storage_, &vtable_);
        }
    }

    function(function& other)
    {
        if (other)
        {
            other.copy_to(storage_, &vtable_);
        }
    }

    template <class F>
    function(F&& f)
    {
        register_callback(std::forward<F>(f));
    }

    ~function()
    {
        if (vtable_.exec)
        {
            vtable_.destructor(&storage_);
        }
    }


    function& operator=(const function& other);

    function& operator=(function&& other) noexcept;

    function& operator=(std::nullptr_t);

    template <class F>
    function& operator=(F&& f);

    template <class F>
    function& operator=(std::reference_wrapper<F> f);

    void swap(function& other) noexcept;

    explicit operator bool() const noexcept
    {
        return vtable_.exec != nullptr;
    }

    ReturnType operator()(Args... args);

    ReturnType operator()(Args... args) const;


private:
    void copy_to(storage_type& new_place, void* vtable) const;

    void move_to(storage_type& new_place, void* vtable) const;

    struct v_table
    {
        v_table()
            : exec{nullptr}, destructor{nullptr}, copy{nullptr}, move{nullptr}
        {
        }
        using executor_type   = ReturnType (*)(void*, Args&&...);
        using destructor_type = void (*)(void*);
        using copy_type       = void (*)(const void*, void*, void* vtable);
        using move_type       = void (*)(const void*, void*, void* vtable);

        executor_type exec;
        destructor_type destructor;
        copy_type copy;
        move_type move;
    };

    v_table vtable_;

    template <typename FunctionType>
    static ReturnType execute(void* data, Args&&... args);

    template <class FunctionType>
    static void delete_callback(void* function);

    template <class FunctionType>
    static void copy(const void* data, void* place, void* vtable);

    template <class FunctionType>
    static void move(const void* data, void* place, void* vtable);

    template <class FunctionType>
    void register_callback(FunctionType&& function);

    storage_type storage_;
};

template <std::size_t Size, class ReturnType, class... Args>
function<ReturnType(Args...), Size>& function<ReturnType(Args...), Size>::operator=(const function& other)
{
    if (vtable_.exec)
    {
        vtable_.destructor(&storage_);
    }
    other.copy_to(storage_, &vtable_);
    return *this;
}

template <std::size_t Size, class ReturnType, class... Args>
function<ReturnType(Args...), Size>& function<ReturnType(Args...), Size>::operator=(function&& other) noexcept
{
    if (vtable_.exec)
    {
        vtable_.destructor(&storage_);
    }
    other.move_to(storage_, &vtable_);
    return *this;
}

template <std::size_t Size, class ReturnType, class... Args>
function<ReturnType(Args...), Size>& function<ReturnType(Args...), Size>::operator=(std::nullptr_t)
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

template <std::size_t Size, class ReturnType, class... Args>
template <class F>
function<ReturnType(Args...), Size>& function<ReturnType(Args...), Size>::operator=(F&& f)
{
    if (vtable_.exec)
    {
        vtable_.destructor(&storage_);
    }
    register_callback(std::forward<F>(f));
    return *this;
}

template <std::size_t Size, class ReturnType, class... Args>
template <class F>
function<ReturnType(Args...), Size>& function<ReturnType(Args...), Size>::operator=(std::reference_wrapper<F> f)
{
    if (vtable_.exec)
    {
        vtable_.destructor(&storage_);
    }
    register_callback(std::forward<F>(f));
    return *this;
}

template <std::size_t Size, class ReturnType, class... Args>
void function<ReturnType(Args...), Size>::swap(function& other) noexcept
{
    auto copy = function(*this);
    *this     = other;
    other     = copy;
}

template <std::size_t Size, class ReturnType, class... Args>
ReturnType function<ReturnType(Args...), Size>::operator()(Args... args)
{
    assert(vtable_.exec != nullptr && "Function not initialized!");
    return vtable_.exec(&storage_, std::forward<Args>(args)...);
}

template <std::size_t Size, class ReturnType, class... Args>
ReturnType function<ReturnType(Args...), Size>::operator()(Args... args) const
{
    assert(vtable_.exec != nullptr && "Function not initialized!");
    return vtable_.exec(&storage_, std::forward<Args>(args)...);
}

template <std::size_t Size, class ReturnType, class... Args>
void function<ReturnType(Args...), Size>::copy_to(storage_type& new_place, void* vtable) const
{
    vtable_.copy(&storage_, &new_place, vtable);
}

template <std::size_t Size, class ReturnType, class... Args>
void function<ReturnType(Args...), Size>::move_to(storage_type& new_place, void* vtable) const
{
    vtable_.move(&storage_, &new_place, vtable);
}

template <std::size_t Size, class ReturnType, class... Args>
template <typename FunctionType>
ReturnType function<ReturnType(Args...), Size>::execute(void* data, Args&&... args)
{
    FunctionType& f = *static_cast<FunctionType*>(data);

    return f(std::forward<Args>(args)...);
}

template <std::size_t Size, class ReturnType, class... Args>
template <class FunctionType>
void function<ReturnType(Args...), Size>::delete_callback(void* function)
{
    FunctionType& f = *static_cast<FunctionType*>(function);
    f.~FunctionType();
}

template <std::size_t Size, class ReturnType, class... Args>
template <class FunctionType>
void function<ReturnType(Args...), Size>::copy(const void* data, void* place, void* vtable)
{
    const FunctionType f = *static_cast<const FunctionType*>(data);
    v_table& vt          = *static_cast<v_table*>(vtable);
    new (place) FunctionType(f);
    vt.exec       = &execute<FunctionType>;
    vt.destructor = &delete_callback<FunctionType>;
    vt.copy       = &copy<FunctionType>;
    vt.move       = &move<FunctionType>;
}

template <std::size_t Size, class ReturnType, class... Args>
template <class FunctionType>
void function<ReturnType(Args...), Size>::move(const void* data, void* place, void* vtable)
{
    const FunctionType& f = *static_cast<const FunctionType*>(data);
    v_table& vt           = *static_cast<v_table*>(vtable);
    new (place) FunctionType(std::move(f));
    vt.exec       = &execute<FunctionType>;
    vt.destructor = &delete_callback<FunctionType>;
    vt.copy       = &copy<FunctionType>;
    vt.move       = &move<FunctionType>;
}

template <std::size_t Size, class ReturnType, class... Args>
template <class FunctionType>
void function<ReturnType(Args...), Size>::register_callback(FunctionType&& function)
{
    using decayed_function_type = typename std::decay<FunctionType>::type;
    static_assert(!std::is_same<decayed_function_type, this_type>::value, "Wrong function type declared");
    static_assert(sizeof(decayed_function_type) <= size, "Buffer overflow. Increase size parameter!");

    // ReSharper disable once CppNonReclaimedResourceAcquisition
    new (&storage_) decayed_function_type(std::forward<FunctionType>(function));

    vtable_.exec       = &execute<decayed_function_type>;
    vtable_.destructor = &delete_callback<decayed_function_type>;
    vtable_.copy       = &copy<decayed_function_type>;
    vtable_.move       = &move<decayed_function_type>;
}
} // namespace eul