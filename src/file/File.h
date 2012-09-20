#ifndef FILE_H_THIS_IS_VERY_UNIQUE_GTSJENFK
#define FILE_H_THIS_IS_VERY_UNIQUE_GTSJENFK
	#ifdef WIN32
		#include "WinFileImpl.h"
		typedef WinFileImpl File;
	#else
		#include "PosixFileImpl.h"
		typedef PosixFileImpl File;
	#endif
#endif // FILE_H_THIS_IS_VERY_UNIQUE_GTSJENFK
