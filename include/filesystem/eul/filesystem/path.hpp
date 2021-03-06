#pragma once

#include <string>
#include <string_view>

#include "eul/filesystem/path_const_iterator.hpp"

namespace eul::filesystem
{

class path
{
public:
    using const_iterator = path_const_iterator;
    using iterator = const_iterator;

    path(std::string_view p); // NOLINT(google-explicit-constructor)
    path(const path& p);
    path(const char* p); // NOLINT(google-explicit-constructor)
    ~path() = default;
    path(path&& p) = default;
    path& operator=(const std::string_view& p);
    path& operator=(const path& p);
    path& operator=(path&& p) = default;
    path& operator=(const char* p);

    [[nodiscard]]
    path lexically_normal() const;
    [[nodiscard]]
    path lexically_relative(const path& base) const;

    [[nodiscard]]
    const char* c_str() const;
    [[nodiscard]]
    const std::string& native() const;
    path root_path();

    [[nodiscard]]
    bool is_absolute() const;

    [[nodiscard]]
    iterator begin() const;
    [[nodiscard]]
    static iterator end();

    [[nodiscard]]
    path parent_path() const;
    [[nodiscard]]
    std::string filename() const;

    path& operator+=(const std::string_view& next);
    path& operator+=(const path& next);

private:
    std::string path_;
};

} // namespace eul::filesystem
