#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

#include "md5.h"

using namespace std;

#ifdef WIN32
    class WinFileImpl;
    typedef  WinFileImpl File;
#else
    class PosixFileImpl;
    typedef PosixFileImpl File;
#endif


class AbstractFile {
protected:
	AbstractFile(string path);

    virtual string getCanonicalName();

    string _path;
    ifstream* _fileStream;

    void openFileStream(void);
    int getRemainingSize(void);

public:
	virtual ~AbstractFile();

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
	virtual string getName();

    virtual void reset();

    string computeMD5(void);
};

#endif // ABSTRACTFILE_H

