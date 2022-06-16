#pragma once

#include <compare>

#include <string>
#include <string_view>

namespace eul::filesystem
{

class path_const_iterator
{
public:
    explicit path_const_iterator(std::string_view path);

    path_const_iterator operator++(int);
    const path_const_iterator& operator++();

    std::string_view operator*() const;

    bool operator==(const path_const_iterator& it) const noexcept = default;
private:
    void set_next_part();
    std::string_view part_;
    std::string_view path_;
};

} // namespace eul::filesystem
