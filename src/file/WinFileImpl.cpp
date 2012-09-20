#include "WinFileImpl.h"

#ifdef WIN32

WinFileImpl::WinFileImpl(string path) : AbstractFile(path), _areAttributesLoaded(false) {

}

WinFileImpl::~WinFileImpl() {

}

long WinFileImpl::loadTimes(void) {
	return GetFileTime(0, &_timeCreated, &_timeLastAccess, &_timeLastWrite);
}

void WinFileImpl::loadAttributes(void) {
	_fileAttributes = GetFileAttributesA(_path.c_str());
}

bool WinFileImpl::isDirectory(void) {
	loadAttributes();

	if (_fileAttributes == INVALID_FILE_ATTRIBUTES) {
		return false;
	}

	if (_fileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		return true;
	}

	return false;
}

bool WinFileImpl::isFile(void) {
	loadAttributes();

	if (_fileAttributes == INVALID_FILE_ATTRIBUTES) {
		// Nb.: if GetLastError() == 2 then "ERROR_FILE_NOT_FOUND".
		return false;
	}

	// Going on a limb here, not sure if this will work as expected.
	return !isDirectory();
}

bool WinFileImpl::exists(void) {
	if (_fileAttributes == INVALID_FILE_ATTRIBUTES) {
		return false;
	}

	return isFile() || isDirectory();
}

long WinFileImpl::lastModified(void) {
	throw exception("Not implemented.");

	if(!loadTimes()) {
		// Someone made a boo-boo :(
		// throw FileException("Cannot determine file. Does the file exist?");
		return -1;
	}

	// FileTimeToSystemTime(&ftWrite, &stUTC) ??
	return 1;
}

// http://msdn.microsoft.com/en-us/library/windows/desktop/aa365200(v=vs.85).aspx
vector<string> WinFileImpl::list() {
	string searchPath = _path;

	searchPath.append("/*");

	WIN32_FIND_DATAA fileData;
	HANDLE filesFound = FindFirstFileA(searchPath.c_str(), &fileData);

	if (filesFound == INVALID_HANDLE_VALUE) {
		cout << "INVALID_HANDLE_VALUE" << endl;
		exit(-1);
	}

	vector<string> files;

	do {
		// NB: The count may seem "weird" but that is due to the null character.
		if(strncmp(fileData.cFileName, ".", 2) == 0 || strncmp(fileData.cFileName, "..", 3) == 0) {
			continue;
		}

		files.push_back(fileData.cFileName);
	} while (FindNextFileA(filesFound, &fileData) != 0);

	if (GetLastError() != ERROR_NO_MORE_FILES) {
		cout << " Broke out of the do while loop for error reasons :( " << endl;
		exit(-1);
	}
	
	FindClose(filesFound);

	return files;
}

#endif // WIN32