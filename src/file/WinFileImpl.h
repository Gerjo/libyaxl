#ifndef WINFILEIMPL_H
#define WINFILEIMPL_H
#ifdef WIN32

#include <Windows.h>
#include <direct.h>

#include "AbstractFile.h"

namespace yaxl {
namespace file {

class WinFileImpl;
typedef WinFileImpl File;

class WinFileImpl : public AbstractFile {
public:
	WinFileImpl(string path);
    virtual ~WinFileImpl();

	virtual bool isDirectory(void);
    virtual bool isFile(void);
	virtual bool exists(void);
	virtual long lastModified(void);
	virtual vector<string> list(void);
	virtual vector<File> listFiles();

protected:
    virtual void mkDir(const string& dirName);

private:
	unsigned long _fileAttributes;
	bool _areAttributesLoaded;

	void loadAttributes(void);
	long loadTimes(void);

	FILETIME _timeCreated;
	FILETIME _timeLastAccess;
	FILETIME _timeLastWrite;
};

}
}

#endif // WIN32
#endif // WINFILEIMPL_H
