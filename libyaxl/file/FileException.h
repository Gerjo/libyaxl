#ifndef FILEEXCEPTION_H
#define	FILEEXCEPTION_H

#include "../common/YaxlException.h"
#include "../common/CompileConfig.h"

namespace yaxl {
    namespace file {
        class LIBEXPORT FileException : public YaxlException {
        public:
            FileException(string error) : YaxlException(error) {

            }
        };
    }
}

#endif	/* FILEEXCEPTION_H */

