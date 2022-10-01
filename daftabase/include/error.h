#ifndef _ERROR_H_
#define _ERROR_H_

#include <exception>
#include <string>

namespace daftabase
{

class Error : std::exception
{
private:
    std::string m_what;

public:
    Error(const std::string& what)
        : m_what(what)
    {
    }

    virtual const char* what() const noexcept
    {
        return m_what.c_str();
    }
};

} // namespace daftabase

#endif /* _ERROR_H_ */
