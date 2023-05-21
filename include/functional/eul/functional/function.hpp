// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <new>
#include <type_traits>
#include <utility>

#include "eul/utils/assert.hpp"

namespace eul
{
template <class, std::size_t>
class function;

template <std::size_t Size, class ReturnType, class... Args>
class function<ReturnType(Args...), Size>
{
    struct IFunctionInvoker // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        virtual ~IFunctionInvoker()                       = default;
        virtual ReturnType operator()(Args... args)       = 0;
        virtual ReturnType operator()(Args... args) const = 0;
        virtual void copy_to(void* new_place) const       = 0;
        virtual void move_to(void* new_place) const       = 0;
    };

public:
    constexpr static std::size_t size = Size + sizeof(IFunctionInvoker) + sizeof(void*);

    using storage_type = std::array<uint8_t, size>;
    using this_type    = function<ReturnType(Args...), size>;

    function() noexcept = default;

    explicit function(std::nullptr_t) noexcept
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
    function(F&& f) // NOLINT(google-explicit-constructor, bugprone-forwarding-reference-overload)
    {
        register_callback(std::forward<F>(f));
    }

    template <class F>
    // cppcheck-suppress  noExplicitConstructor
    function(const F& f) // NOLINT(google-explicit-constructor)
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
        if (this == &other)
        {
            return *this;
        }

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
        register_callback(std::forward<F>(f));
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
        eul_assert_msg(isCallable_ != false, "Function not initialized!");
        auto& invoker = get_invoker();
        return invoker(args...);
    }

    ReturnType operator()(Args... args) const
    {
        eul_assert_msg(isCallable_ != false, "Function not initialized!");
        const auto& invoker = get_invoker();
        return invoker(args...);
    }


protected:
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
        FunctionInvoker()                                                    = default;
        ~FunctionInvoker() override                                          = default;
        FunctionInvoker(const FunctionInvoker&)                              = default;
        FunctionInvoker(FunctionInvoker&&) noexcept                          = default;
        FunctionInvoker<FunctionType>& operator=(FunctionInvoker&&) noexcept = default;
        FunctionInvoker<FunctionType>& operator=(const FunctionInvoker&)     = default;

        explicit FunctionInvoker(FunctionType&& function) noexcept
            : function_(std::move(function))
        {
        }

        explicit FunctionInvoker(const FunctionType& function)
            : function_(function)
        {
        }

        ReturnType operator()(Args... args) override
        {
            return function_(args...);
        }

        ReturnType operator()(Args... args) const override
        {
            return function_(args...);
        }

        void copy_to(void* new_place) const override
        {
            new (new_place) FunctionInvoker(*this);
        }

        void move_to(void* new_place) const override
        {
            new (new_place) FunctionInvoker(std::move(*this));
        }

    private:
        [[no_unique_address]] FunctionType function_;
    };


    [[nodiscard]] IFunctionInvoker& get_invoker()
    {
        return *std::bit_cast<IFunctionInvoker*>(&storage_);
    }

    [[nodiscard]] const IFunctionInvoker& get_invoker() const
    {
        return *std::bit_cast<const IFunctionInvoker*>(&storage_);
    }

    template <class FunctionType>
    void register_callback(FunctionType&& f)
    {
        using decayed_function_type = typename std::decay_t<FunctionType>;
        using function_invoker_type = FunctionInvoker<decayed_function_type>;
        static_assert(!std::is_same<decayed_function_type, this_type>::value, "Wrong function type declared");
        static_assert(sizeof(function_invoker_type) <= size, "Buffer overflow. Increase size parameter!");

        new (&storage_) function_invoker_type(std::forward<FunctionType>(f));
        isCallable_ = true;
    }

    template <class FunctionType>
    void register_callback(const FunctionType& f)
    {
        using decayed_function_type = typename std::decay_t<FunctionType>;
        using function_invoker_type = FunctionInvoker<decayed_function_type>;
        static_assert(!std::is_same<decayed_function_type, this_type>::value, "Wrong function type declared");
        static_assert(sizeof(function_invoker_type) <= size, "Buffer overflow. Increase size parameter!");

        new (&storage_) function_invoker_type(f);
        isCallable_ = true;
    }

private:
    alignas(alignof(void*)) storage_type storage_{};
    bool isCallable_{false};
};

} // namespace eul
