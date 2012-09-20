#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class AbstractFile {
protected:
	AbstractFile(string path);
    
    string _path;

public:
	virtual ~AbstractFile();

    virtual bool isDirectory(void) = 0;
    virtual bool isFile(void) = 0;
	virtual bool exists(void) = 0;
	virtual long lastModified(void) = 0;
	virtual vector<string> list(void) = 0;

	virtual string getName();
};

#endif // ABSTRACTFILE_H

