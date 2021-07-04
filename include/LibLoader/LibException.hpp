/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#ifndef LIBEXCEPTION_HPP
#define LIBEXCEPTION_HPP

#include <stdexcept>

namespace LibLoader
{
    class CLibException : public std::exception
    {
        public:
            CLibException(const std::string &Msg) : m_Msg(Msg) {}
    
            const char *what() const noexcept override
            {
                return m_Msg.c_str();
            }    
        private:
            std::string m_Msg;
    };
} // namespace LibLoader

#endif //LIBEXCEPTION_HPP