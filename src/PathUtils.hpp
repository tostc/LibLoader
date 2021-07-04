/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#ifndef PATHUTILS_HPP
#define PATHUTILS_HPP

#include <algorithm>
#include <string>

namespace LibLoader
{
    inline std::string GetFilename(std::string Path)
    {
        std::replace(Path.begin(), Path.end(), '\\', '/');
        size_t Pos = Path.find_last_of('/');

        if(Pos != std::string::npos)
            Path = Path.substr(Pos + 1);

        return Path;
    }

    inline std::string ChangeFilename(std::string Path, const std::string &Filename)
    {
        std::string TmpPath = Path;

        std::replace(TmpPath.begin(), TmpPath.end(), '\\', '/');
        size_t Pos = TmpPath.find_last_of('/');

        if(Pos != std::string::npos)
            Path = Path.substr(0, Pos + 1);

        return Path + Filename;
    }
} // namespace LibLoader

#endif //PATHUTILS_HPP