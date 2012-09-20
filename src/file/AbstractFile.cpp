#include "AbstractFile.h"


AbstractFile::AbstractFile(string path) : _path(path) {

}

AbstractFile::~AbstractFile() {

}

string AbstractFile::getName() {
	return _path;
}

string AbstractFile::getCononicalName() {
    string name = getName();
    int len     = name.length();

    while(name.substr(len - 1, len).compare("/") == 0) {
        name = name.substr(0, len -1);
        len  = name.length();
    }

    // Hmmmz:
    //std::remove(name.begin(), name.end(), '/');

    return name;
}