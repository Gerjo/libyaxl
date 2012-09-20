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
#include <fstream>
#include <sstream>

#include "AbstractFile.h"


class PosixFileImpl;
typedef PosixFileImpl File;

using namespace std;

class PosixFileImpl : public AbstractFile {
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
    virtual string readAll();
    virtual string readLine();
    virtual string readSome(int len);


private:
    int loadStat(void);
    struct stat statDetails;
};

#endif  /* !WIN32 */
#endif	/* POSIXFILEIMPL_H */

