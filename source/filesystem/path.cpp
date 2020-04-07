#include "eul/filesystem/path.hpp"

namespace eul
{
namespace filesystem
{

path::path(const std::string_view& p)
    : path_(p)
{
}

path path::create(const std::string_view& p)
{
    return path(p);
}

bool path::is_absolute() const
{
    return path_.empty() ? false : path_[0] == '/';
}

path path::lexically_normal()
{
    std::string converted_path;
    for (const auto& part : *this)
    {
        if (part == ".")
        {
            continue;
        }
        else if (part == "..")
        {
            if (!converted_path.empty())
            {
                std::size_t last_slash = converted_path.find_last_of("/");
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

path::iterator path::end() const
{
    return path_const_iterator("");
}

path& path::operator+=(const std::string_view& next)
{
    path_ += "/";
    path_ += next;
    return *this;
}

path& path::operator+=(const path& next)
{
    path_ += "/";
    path_ += next.path_;
    return *this;
}



} // namespace filesystem
} // namespace eul
