/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#include <LibLoader/LibException.hpp>
#include "../PathUtils.hpp"
#include "UnixLibHandle.hpp"

namespace LibLoader
{
    CUnixLibHandle::CUnixLibHandle(const std::string &Path)
    {
        const char *SOFilePath = nullptr;
        if(!Path.empty())
        {
            std::string LibName = GetFilename(Path);
            if(LibName.find("lib") == std::string::npos)
                LibName = "lib" + LibName;

            if(LibName.find(".so") == std::string::npos)
                LibName += ".so";

            m_Name = LibName;
            m_FullPath = ChangeFilename(Path, LibName);
            std::replace(m_FullPath.begin(), m_FullPath.end(), '\\', '/');

            SOFilePath = m_FullPath.c_str();
        }
        else
            m_Name = "Executable";

        m_SOHandle = dlopen(SOFilePath, RTLD_LAZY);
        if(m_SOHandle == nullptr)
            throw CLibException(dlerror());
    }

    CUnixLibHandle::~CUnixLibHandle() 
    {
        dlclose(m_SOHandle);
    }

    void *CUnixLibHandle::LoadNativeFunction(const std::string &FuncName)
    {
        void *Ref = dlsym(m_SOHandle, FuncName.c_str());
        if(Ref == nullptr)
            throw CLibException(dlerror());

        return Ref;
    }
} // namespace LibLoader
