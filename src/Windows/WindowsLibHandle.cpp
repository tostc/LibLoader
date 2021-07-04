/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#include <LibLoader/LibException.hpp>
#include "../PathUtils.hpp"
#include "WindowsLibHandle.hpp"

namespace LibLoader
{
    CWindowsLibHandle::CWindowsLibHandle(const std::string &Path)
    {
        const char *DLLFilePath = nullptr;
        if(!Path.empty())
        {
            std::string LibName = GetFilename(Path);
            if(LibName.find(".dll") == std::string::npos)
                LibName += ".dll";

            m_Name = LibName;
            m_FullPath = ChangeFilename(Path, LibName);
            std::replace(m_FullPath.begin(), m_FullPath.end(), '/', '\\');

            DLLFilePath = m_FullPath.c_str();
        }
        else
            m_Name = "Executable";

        if(DLLFilePath != nullptr)
            m_Handle = LoadLibraryA(DLLFilePath);
        else
            m_Handle = GetModuleHandle(nullptr);

        if(m_Handle == nullptr)
            throw CLibException("Couldn't load library: '" + m_FullPath + "' Error: " + GetError());
    }

    CWindowsLibHandle::~CWindowsLibHandle() 
    {
        FreeLibrary(m_Handle);
    }

    void *CWindowsLibHandle::LoadNativeFunction(const std::string &FuncName)
    {
        void *Ref = (void*)GetProcAddress(m_Handle, FuncName.c_str());
        if(Ref == nullptr)
            throw CLibException("Couldn't load function: '" + FuncName + "' Error: " + GetError());

        return Ref;
    }

    // https://docs.microsoft.com/en-us/windows/win32/debug/retrieving-the-last-error-code
    std::string CWindowsLibHandle::GetError()
    {
        std::string Ret;

        LPSTR lpMsgBuf;
        DWORD dw = GetLastError(); 

        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            NULL, 
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
            (LPSTR)&lpMsgBuf, 
            0, NULL);

        Ret = lpMsgBuf;
        LocalFree(lpMsgBuf);

        return Ret;
    }
} // namespace LibLoader
