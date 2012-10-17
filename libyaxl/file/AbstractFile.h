#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

#include "md5.h"
#include "../common/CompileConfig.h"

namespace yaxl {
namespace file {

using namespace std;

#ifdef WIN32
    class WinFileImpl;
    typedef  WinFileImpl File;
#else
    class PosixFileImpl;
    typedef PosixFileImpl File;
#endif


class LIBEXPORT AbstractFile {
protected:
	AbstractFile(string path);

    virtual string getCanonicalName();

    string _path;
    ifstream* _inputFileStream;

    void closeStreams(void);
    void openInputFileStream(bool createFile = false);
    int getRemainingSize(void);

    // OS specific implementation. The other mkDir methods will
    // simply call this one.
    virtual void mkDir(const string& dirName) = 0;



public:
	virtual ~AbstractFile(void);

    virtual bool isDirectory(void) = 0;
    virtual bool isFile(void) = 0;
	virtual bool exists(void) = 0;
	virtual long lastModified(void) = 0;
	virtual vector<string> list(void) = 0;
    virtual vector<File> listFiles() = 0;


    virtual int size();
    virtual string readAll();
    virtual string readLine();
    virtual string readLine(const char& delimiter);
    virtual string readSome(int len);
	virtual string getName(void);

    virtual void mkDir(void);
    virtual void mkDirs(void);

    virtual void write(const string& data);
    virtual void write(const char* data, const int length);
    virtual void append(const string& data);
    virtual void append(const char* data, const int length);
    virtual void reset();

    virtual bool createNewFile(void);

    string computeMD5(void);

    virtual bool remove(void);
};

}
}

#endif // ABSTRACTFILE_H

