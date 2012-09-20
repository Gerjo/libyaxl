#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

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

    virtual string getCononicalName();

    string _path;

public:
	virtual ~AbstractFile();

    virtual bool isDirectory(void) = 0;
    virtual bool isFile(void) = 0;
	virtual bool exists(void) = 0;
	virtual long lastModified(void) = 0;
	virtual vector<string> list(void) = 0;
    virtual vector<File> listFiles() = 0;

    virtual int size() = 0;
    virtual stringstream readAll() = 0;
    virtual stringstream readLine() = 0;
    virtual stringstream readSome(int len) = 0;


    string readAll() {
        stringstream tmp = readAll();
        return tmp.str();
    }

	virtual string getName();
};

#endif // ABSTRACTFILE_H

