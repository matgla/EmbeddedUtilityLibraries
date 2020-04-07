#include "eul/filesystem/path_const_iterator.hpp"

namespace eul
{
namespace filesystem
{

path_const_iterator::path_const_iterator(std::string_view path)
    : path_(path)
{
    set_next_part();
}

path_const_iterator path_const_iterator::operator++(int)
{
    path_const_iterator old = *this;
    set_next_part();
    return old;
}
path_const_iterator& path_const_iterator::operator++()
{
    set_next_part();
    return *this;
}

std::string_view path_const_iterator::operator*() const
{
    return part_;
}

bool path_const_iterator::operator==(const path_const_iterator& it) const
{
    return part_ == it.part_ && path_ == it.path_;
}

bool path_const_iterator::operator!=(const path_const_iterator& it) const
{
    return !operator==(it);
}

void path_const_iterator::set_next_part()
{
    if (part_.empty())
    {
        std::size_t first_slash = path_.find("/");
        if (first_slash == 0)
        {
            part_ = path_.substr(0, 1);
            path_ = path_.substr(1, path_.length());
            return;
        }
    }
    std::size_t first_not_slash = path_.find_first_not_of("/");
    if (first_not_slash != std::string_view::npos)
    {
        path_ = path_.substr(first_not_slash, path_.length());
        std::size_t first_slash = path_.find("/");

        if (first_slash != std::string_view::npos)
        {
            part_ = path_.substr(0, first_slash);
            path_ = path_.substr(part_.length(), path_.length());
            return;
        }

        part_ = path_;
        path_ = {};
        return;
    }
    path_ = {};
    part_ = {};
}

} // namespace filesystem
} // namespace eul
