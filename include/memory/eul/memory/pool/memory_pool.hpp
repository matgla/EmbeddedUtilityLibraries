// // This file is part of EUL project. This project is set of libraries useful for embedded development.
// // Copyright (C) 2019 Mateusz Stadnik
// //
// // This program is free software: you can redistribute it and/or modify
// // it under the terms of the GNU General Public License as published by
// // the Free Software Foundation, either version 3 of the License, or
// // (at your option) any later version.
// //
// // This program is distributed in the hope that it will be useful,
// // but WITHOUT ANY WARRANTY; without even the implied warranty of
// // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// // GNU General Public License for more details.
// //
// // You should have received a copy of the GNU General Public License
// // along with this program.  If not, see <https://www.gnu.org/licenses/>.

// #include <array>
// #include <cstddef>
// #include <string>
// #include <type_traits>

// #include <gsl/pointers>

// #include "eul/memory/pool/details/allocation_header.hpp"
// #include "eul/memory/pool/unique_ptr.hpp"
// #include "eul/utils/unused.hpp"

// namespace eul::memory::pool
// {

// constexpr std::size_t default_pool_size = 128;
// template <std::size_t Size = default_pool_size, typename AlignmentType = std::max_align_t>
// struct memory_pool
// {
// public:
//     constexpr static uint8_t alignment = alignof(AlignmentType);
//     using storage_type = typename std::aligned_storage<sizeof(uint8_t), alignment>::type;
//     using self_type = memory_pool<Size, AlignmentType>;


//     memory_pool() = default;

//     template <typename T, typename... Args>
//     auto allocate(Args&&... args)
//     {
//         UNUSED(std::forward<Args>(args)...);
//         static_assert(alignof(T) <= alignment, "Can't allocate object with higher alignment than memory pool has!");
//         constexpr std::size_t header_size = align(sizeof(details::allocation_header));
//         constexpr std::size_t allocation_size = align(sizeof(T));

//         const auto deallocation_callback = [this](const auto* pool_ptr)
//         {
//             if (pool_ptr)
//             {
//                 this->deallocate(*pool_ptr);
//             }
//         };

//         if (header_size + allocation_size >= Size - current_)
//         {
//             return make_unique_ptr<T>(nullptr, deallocation_callback);
//         }

//         new (&data_.at(current_)) details::allocation_header(details::allocation_header::State::Reserved, allocation_size);
//         const auto header_position_in_buffer = current_;

//         current_ += header_size;
//         gsl::owner<T*> object = new (&data_.at(current_)) T{std::forward<Args>(args)...}; // NOLINT(modernize-use-auto)
//         current_ += allocation_size;

//         return make_unique_ptr(object, deallocation_callback, header_position_in_buffer);
//     }

//     void deallocate(const auto& data)
//     {
//         (void)(data);
//     }
// private:
//     template <typename T>
//     constexpr static T align(T a)
//     {
//         return a % alignment ? a + (alignment - a % alignment) : a;
//     }

//     std::size_t start_{0};
//     std::size_t current_{0};
//     std::size_t end_{0};
//     std::array<storage_type, Size> data_{};
// };

// } // namespace eul::memory::pool
