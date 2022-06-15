#include "eul/filesystem/path.hpp"

// TODO(mateusz): Remove std::string, should be replaced with some custom string with known size

namespace eul::filesystem
{

path::path(std::string_view path)
    : path_(path)
{
}

path::path(const path& path) = default;

path::path(const char* path)
    : path_(path)
{
}

path& path::operator=(const path& path)
{
    if (this != &path)
    {
        this->path_ = path.path_;
    }
    return *this;
}


path& path::operator=(const std::string_view& path)
{
    path_ = path;
    return *this;
}

path& path::operator=(const char* path)
{
    path_ = path;
    return *this;
}



bool path::is_absolute() const
{
    return path_.empty() ? false : path_[0] == '/';
}

void path::convert_slashes(std::string& converted_path) const
{
    if (!converted_path.empty())
    {
        std::size_t last_slash = converted_path.find_last_of('/');
        if (last_slash != std::string::npos)
        {
            converted_path = converted_path.substr(0, last_slash);
            if (converted_path.empty())
            {
                converted_path = "/";
            }
        }
        else
        {
            if (is_absolute())
            {
                converted_path = "/";
            }
            else
            {
                if (converted_path.find("..") != std::string::npos)
                {
                    converted_path += "/";
                    converted_path += "..";
                }
                else if (converted_path == ".")
                {
                    converted_path = "..";
                }
                else
                {
                    converted_path = ".";
                }
            }
        }
    }
    else
    {
        if (is_absolute())
        {
            converted_path = "/";
        }
        else
        {
            converted_path = "..";
        }
    }
}


// TODO(mateusz): rewrite this, it's quite complex
path path::lexically_normal() const
{
    std::string converted_path;
    for (const auto part : *this) // NOLINT(readability-static-accessed-through-instance)
    {
        if (part == ".")
        {
            continue;
        }

        if (part == "..")
        {
            convert_slashes(converted_path);
        }
        else
        {
            if (!converted_path.empty() && converted_path != "/")
            {
                converted_path += "/";
            }
            converted_path += part;
        }
    }

    converted_path.shrink_to_fit();
    return path{converted_path};
}

path path::lexically_relative(const path& base) const
{
    if (path_.starts_with(base.path_))
    {
        std::string relative = path_.substr(base.path_.length(), path_.length());
        std::size_t first_not_slash = relative.find_first_not_of('/');
        if (first_not_slash != std::string_view::npos)
        {
            relative = relative.substr(first_not_slash, relative.length());
        }
        return {relative};
    }
    return {""};
}

path path::parent_path() const
{
    std::size_t last_slash = path_.find_last_of('/');
    if (last_slash == std::string::npos)
    {
        return {""};
    }

    if (last_slash == 0)
    {
        return {"/"};
    }

    return {path_.substr(0, last_slash)};
}

std::string path::filename() const
{
    std::size_t last_slash = path_.find_last_of('/');
    if (last_slash == std::string::npos || last_slash == path_.length())
    {
        return path_;
    }
    return path_.substr(last_slash + 1, path_.length());
}

const std::string& path::native() const
{
    return path_;
}

const char* path::c_str() const
{
    return path_.c_str();
}

path::iterator path::begin() const
{
    return path_const_iterator(path_);
}

path::iterator path::end()
{
    return path_const_iterator("");
}

path& path::operator+=(const std::string_view& next)
{
    if (path_ != "/")
    {
        path_ += "/";
    }
    path_ += next;
    return *this;
}

path& path::operator+=(const path& next)
{
    if (path_ != "/")
    {
        path_ += "/";
    }
    path_ += next.path_;
    return *this;
}

} // namespace eul::filesystem
