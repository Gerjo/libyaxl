#ifndef FILEEXCEPTION_H
#define	FILEEXCEPTION_H

#include "../common/YaxlException.h"


namespace yaxl {
    namespace file {
        class FileException : public YaxlException {
        public:
            FileException(string error) : YaxlException(error) {
                
            }
        };
    }
}

#endif	/* FILEEXCEPTION_H */

