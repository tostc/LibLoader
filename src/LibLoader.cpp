/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#include <LibLoader/LibLoader.hpp>

#if defined (_WIN32) || defined (_WIN64)
    #include "Windows/WindowsLibHandle.hpp"
    #undef LoadLibrary
#else
    #include "Unix/UnixLibHandle.hpp"
#endif

#include <map>

namespace LibLoader
{
    std::map<std::string, LibHandle> m_LoadedLibraries;

    LibHandle LoadLibrary(const std::string &Path)
    {
        auto IT = m_LoadedLibraries.find(Path);
        if(IT != m_LoadedLibraries.end())
            return IT->second;

#if defined (_WIN32) || defined (_WIN64)
        return LibHandle(new CWindowsLibHandle(Path));
#else
        return LibHandle(new CUnixLibHandle(Path));
#endif
    }

    void UnloadLibrary(LibHandle Library)
    {
        auto IT = m_LoadedLibraries.find(Library->FullPath());
        if(IT != m_LoadedLibraries.end())
            m_LoadedLibraries.erase(IT);
    }

    std::vector<LibHandle> GetLoadedLibraries()
    {
        std::vector<LibHandle> Ret;

        for (auto &&lib : m_LoadedLibraries)
            Ret.push_back(lib.second);

        return Ret;
    }
} // namespace LibLoader
