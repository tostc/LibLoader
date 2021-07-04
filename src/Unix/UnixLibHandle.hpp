/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#ifndef UNIXLIBHANDLE_HPP
#define UNIXLIBHANDLE_HPP

#include <dlfcn.h>
#include <LibLoader/LibHandle.hpp>

namespace LibLoader
{
    class CUnixLibHandle : public ILibHandle
    {
        public:
            CUnixLibHandle(const std::string &Path);
            ~CUnixLibHandle();

        protected:
            void *LoadNativeFunction(const std::string &FuncName) override;

        private:
            void *m_SOHandle;
    };
} // namespace LibLoader


#endif //UNIXLIBHANDLE_HPP