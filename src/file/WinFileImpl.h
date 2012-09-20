#ifndef WINFILEIMPL_H
#define WINFILEIMPL_H
#ifdef WIN32

#include <Windows.h>

#include "AbstractFile.h"

class WinFileImpl : public AbstractFile {
public:
	WinFileImpl(string path);
    virtual ~WinFileImpl();

	virtual bool isDirectory(void);
    virtual bool isFile(void);
	virtual bool exists(void);
	virtual long lastModified(void);
	virtual vector<string> list(void);

private:
	unsigned long _fileAttributes;
	bool _areAttributesLoaded;

	void loadAttributes(void);
	long loadTimes(void);

	FILETIME _timeCreated;
	FILETIME _timeLastAccess;
	FILETIME _timeLastWrite;
};

#endif // WIN32
#endif // WINFILEIMPL_H
