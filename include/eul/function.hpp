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
    template <class FunctionType>
    function(FunctionType&& function)
    {
        registerCallback(function);
    }

    ReturnType operator()(Args... args)
    {
        assert(vtable.exec != nullptr && "Function not initialized!");
        return vtable.exec(&storage_, std::forward<Args>(args)...);
    }

    function()
        : vtable{nullptr}
    {
    }

    ~function()
    {
        if (vtable.exec)
        {
            vtable.destructor(&storage_);
        }
    }

private:
    struct VTable
    {
        using Executor   = ReturnType (*)(void*, Args&&...);
        using Destructor = void (*)(void*);
        Executor exec;
        Destructor destructor;
    };
    VTable vtable;

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
    void registerCallback(FunctionType&& function)
    {
        using DecayedFunctionType = typename std::decay<FunctionType>::type;
        using This                = eul::function<ReturnType(Args...), size>;
        static_assert(!std::is_same<DecayedFunctionType, This>::value, "Wrong function type declared");
        static_assert(sizeof(DecayedFunctionType) <= size, "Buffer overflow. Increase size parameter!");

        new (&storage_) DecayedFunctionType(std::forward<FunctionType>(function));

        vtable.exec       = &execute<DecayedFunctionType>;
        vtable.destructor = &deleteCallback<DecayedFunctionType>;
    }

    constexpr static std::size_t size = Size;
    using StorageType                 = typename std::aligned_storage<size, 8>::type;
    StorageType storage_;
};
} // namespace eul