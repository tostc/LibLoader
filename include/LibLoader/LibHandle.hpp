/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#ifndef LIBHANDLE_HPP
#define LIBHANDLE_HPP

#include <functional>
#include <string>
#include <memory>

namespace LibLoader
{
    class ILibHandle
    {
        public:
            /**
             * @brief Loads a function from this library.
             * 
             * @param FuncName: Name of the function.
             * 
             * @return Returns a std::function.
             * 
             * @throw Throws CLibException if any error occurs.
             */
            template<class Ret, class ...Args>
            std::function<Ret(Args...)> LoadFunction(const std::string &FuncName)
            {
                using FuncPointer = Ret(*)(Args...);
                auto Ptr = (FuncPointer)LoadNativeFunction(FuncName);

                std::function<Ret(Args...)> RetFunc;
                RetFunc = [Ptr](Args ...args) 
                {
                    return Ptr(args...);
                };

                return RetFunc;
            }

            /**
             * @return Gets the name of the library.
             */
            inline std::string Name()
            {
                return m_Name;
            }

            /**
             * @return Gets the full path of the library.
             */
            inline std::string FullPath()
            {
                return m_FullPath;
            }

            virtual ~ILibHandle() = default;
        protected:
            virtual void *LoadNativeFunction(const std::string &FuncName) = 0;

            std::string m_Name;
            std::string m_FullPath;
    };

    using LibHandle = std::shared_ptr<ILibHandle>;
} // namespace LibLoader


#endif //LIBHANDLE_HPP