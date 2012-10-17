#ifndef FILE_H_THIS_IS_VERY_UNIQUE_GTSJENFK
#define FILE_H_THIS_IS_VERY_UNIQUE_GTSJENFK

#ifdef WIN32
    #include "WinFileImpl.h"
#else
    #include "PosixFileImpl.h"
#endif

#include "../common/CompileConfig.h"

namespace yaxl {
namespace file {

	#ifdef WIN32
		typedef WinFileImpl File;
	#else
		typedef PosixFileImpl File;
	#endif

}
}

#endif // FILE_H_THIS_IS_VERY_UNIQUE_GTSJENFK
