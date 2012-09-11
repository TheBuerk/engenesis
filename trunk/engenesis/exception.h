#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <exception>
#include <string>
#include <sstream>

namespace egn
{

    class exception : public std::exception
    {
        public:
            exception(const std::string& what, const std::string& file = "", int line = 0) throw()
            {
                std::ostringstream oss;
                oss << file << " line " << line << " : " << what;
                mWhat = oss.str();
            }

            virtual ~exception() throw() {}

            virtual const char* what() const throw()
            {
                return mWhat.c_str();
            }

        private:
            std::string     mWhat;
    };

}

#endif // EXCEPTION_H_INCLUDED
