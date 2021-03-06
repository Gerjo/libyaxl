#ifndef POSIXFILEIMPL_H
#define	POSIXFILEIMPL_H

#ifndef WIN32

#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>

#include "AbstractFile.h"
#include "../common/CompileConfig.h"
#include "FileException.h"

namespace yaxl {
namespace file {

class PosixFileImpl;
typedef PosixFileImpl File;

using namespace std;

class LIBEXPORT PosixFileImpl : public AbstractFile {
public:
    PosixFileImpl(string path);
    virtual ~PosixFileImpl();

    virtual bool isDirectory(void);
    virtual bool isFile(void);
    virtual bool exists(void);
	virtual long lastModified(void);
	virtual vector<string> list(void);
    virtual vector<File> listFiles();

    virtual int size();

protected:
    virtual void mkDir(const string& dirName);

private:
    int loadStat(void);
    struct stat statDetails;
};

}
}

#endif  /* !WIN32 */
#endif	/* POSIXFILEIMPL_H */

