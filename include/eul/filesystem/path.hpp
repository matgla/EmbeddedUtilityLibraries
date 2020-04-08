#pragma once

#include <string>
#include <string_view>

#include "eul/filesystem/path_const_iterator.hpp"

namespace eul
{
namespace filesystem
{

class path
{
public:
    using const_iterator = path_const_iterator;
    using iterator = const_iterator;

    path(std::string_view p);
    path(const char* p);
    path& operator=(const std::string_view& p);

    path lexically_normal() const;
    path lexically_relative(const path& base) const;

    const char* c_str() const;
    const std::string& native() const;
    path root_path();

    bool is_absolute() const;

    iterator begin() const;
    iterator end() const;

    path parent_path() const;
    std::string filename() const;

    path& operator+=(const std::string_view& next);
    path& operator+=(const path& next);

private:
    std::string path_;
};

} // namespace filesystem
} // namespace eul
