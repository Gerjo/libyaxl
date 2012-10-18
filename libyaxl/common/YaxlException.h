#ifndef YAXLEXCEPTION_H
#define	YAXLEXCEPTION_H

#include <exception>
#include <string>
#include <iostream>
#include "../common/CompileConfig.h"

using namespace std;

namespace yaxl {
    class LIBEXPORT YaxlException : public exception {
    public:
        YaxlException(const string error) : _error(error) {
            #ifdef WIN32
                std::cout << "Exception: what(): " << what() << std::endl;
            #endif
        }

        const char* what() const throw() {
            return _error.c_str();
        }

        virtual ~YaxlException() throw() {

        }
    private:
        string _error;
    };
}

#endif	/* YAXLEXCEPTION_H */

