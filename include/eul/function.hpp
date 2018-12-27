#pragma once

#include <cassert>
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
    struct IFunctionInvoker
    {
        virtual ~IFunctionInvoker()                       = default;
        virtual ReturnType operator()(Args... args)       = 0;
        virtual ReturnType operator()(Args... args) const = 0;
        virtual void copy_to(void* new_place) const       = 0;
        virtual void move_to(void* new_place) const       = 0;
    };

public:
    constexpr static std::size_t size
        = Size + sizeof(IFunctionInvoker) + sizeof(void*);

    using storage_type = typename std::aligned_storage<size, 8>::type;
    using this_type    = function<ReturnType(Args...), size>;

    function() noexcept : isCallable_(false)
    {
    }

    explicit function(std::nullptr_t) noexcept : isCallable_(false)
    {
    }

    function(const function& other)
    {
        if (other)
        {
            other.copy_to(storage_);
            isCallable_ = true;
        }
        else
        {
            isCallable_ = false;
        }
    }

    function(function&& other) noexcept
    {
        if (other)
        {
            other.move_to(storage_);
            isCallable_ = true;
        }
        else
        {
            isCallable_ = false;
        }
    }

    function(function& other)
    {
        if (other)
        {
            other.copy_to(storage_);
            isCallable_ = true;
        }
        else
        {
            isCallable_ = false;
        }
    }

    template <class F>
    // cppcheck-suppress  noExplicitConstructor
    function(F&& f)
    {
        register_callback(std::forward<F>(f));
    }

    template <class F>
    // cppcheck-suppress  noExplicitConstructor
    function(const F& f)
    {
        register_callback(f);
    }

    ~function()
    {
        destroy();
    }

    void destroy()
    {
        if (isCallable_)
        {
            get_invoker().~IFunctionInvoker();
            isCallable_ = false;
        }
    }

    function& operator=(const function& other)
    {
        destroy();
        if (other)
        {
            other.copy_to(storage_);
            isCallable_ = true;
        }
        else
        {
            isCallable_ = false;
        }

        return *this;
    }

    function& operator=(function&& other) noexcept
    {
        destroy();
        if (other)
        {
            other.move_to(storage_);
            isCallable_ = true;
        }
        else
        {
            isCallable_ = false;
        }

        return *this;
    }

    function& operator=(std::nullptr_t)
    {
        destroy();
        isCallable_ = false;
        return *this;
    }

    template <class F>
    function& operator=(F&& f)
    {
        destroy();
        register_callback(std::move(f));
        return *this;
    }

    template <class F>
    function& operator=(const F& f)
    {
        destroy();
        register_callback(f);
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
        return isCallable_;
    }

    ReturnType operator()(Args... args)
    {
        assert(isCallable_ != false && "Function not initialized!");
        auto& invoker = get_invoker();
        return invoker(std::forward<Args>(args)...);
    }

    ReturnType operator()(Args... args) const
    {
        assert(isCallable_ != false && "Function not initialized!");
        const auto& invoker = get_invoker();
        return invoker(std::forward<Args>(args)...);
    }


private:
    void copy_to(storage_type& new_place) const
    {
        get_invoker().copy_to(&new_place);
    }

    void move_to(storage_type& new_place) const
    {
        get_invoker().move_to(&new_place);
    }


    template <typename FunctionType>
    struct FunctionInvoker : IFunctionInvoker
    {
        FunctionInvoker(const FunctionInvoker&) = default;
        FunctionInvoker(FunctionInvoker&&)      = default;
        explicit FunctionInvoker(FunctionType&& function) : function_(function)
        {
        }

        explicit FunctionInvoker(const FunctionType& function)
            : function_(function)
        {
        }

        ~FunctionInvoker() = default;

        virtual ReturnType operator()(Args... args) override
        {
            return function_(args...);
        }

        virtual ReturnType operator()(Args... args) const override
        {
            return function_(args...);
        }

        virtual void copy_to(void* new_place) const override
        {
            new (new_place) FunctionInvoker(*this);
        }

        virtual void move_to(void* new_place) const override
        {
            new (new_place) FunctionInvoker(std::move(*this));
        }

        FunctionType function_;
    };


    IFunctionInvoker& get_invoker()
    {
        return *reinterpret_cast<IFunctionInvoker*>(&storage_);
    }

    const IFunctionInvoker& get_invoker() const
    {
        return *reinterpret_cast<const IFunctionInvoker*>(&storage_);
    }

    template <class FunctionType>
    void register_callback(FunctionType&& function)
    {
        using decayed_function_type = typename std::decay<FunctionType>::type;
        using function_invoker_type = FunctionInvoker<decayed_function_type>;
        static_assert(!std::is_same<decayed_function_type, this_type>::value,
                      "Wrong function type declared");
        static_assert(sizeof(function_invoker_type) <= size,
                      "Buffer overflow. Increase size parameter!");

        new (&storage_)
            function_invoker_type(std::forward<FunctionType>(function));
        isCallable_ = true;
    }

    template <class FunctionType>
    void register_callback(const FunctionType& function)
    {
        using decayed_function_type = typename std::decay<FunctionType>::type;
        using function_invoker_type = FunctionInvoker<decayed_function_type>;
        static_assert(!std::is_same<decayed_function_type, this_type>::value,
                      "Wrong function type declared");
        static_assert(sizeof(function_invoker_type) <= size,
                      "Buffer overflow. Increase size parameter!");

        new (&storage_) function_invoker_type(function);
        isCallable_ = true;
    }


    storage_type storage_;
    bool isCallable_;
};

} // namespace eul