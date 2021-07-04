/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#ifndef UNIXDLLHANDLE_HPP
#define UNIXDLLHANDLE_HPP

#include <windows.h>
#include <LibLoader/LibHandle.hpp>

namespace LibLoader
{
    class CWindowsLibHandle : public ILibHandle
    {
        public:
            CWindowsLibHandle(const std::string &Path);
            ~CWindowsLibHandle();

        protected:
            void *LoadNativeFunction(const std::string &FuncName) override;

        private:
            std::string GetError();

            HMODULE m_Handle;
    };
} // namespace LibLoader


#endif //UNIXDLLHANDLE_HPP