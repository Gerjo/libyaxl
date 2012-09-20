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



string AbstractFile::readAll() {
    ifstream fileStream;
    fileStream.open(_path.c_str(), ios::in|ios::binary|ios::ate);

    const int length = fileStream.tellg();
    char memblock[length];

    fileStream.seekg(0, ios::beg);
    fileStream.read(memblock, length);
    fileStream.close();

    string asString(memblock, length);

    return asString;
}

string AbstractFile::readLine() {
    //stringstream meh;

    //return meh;
}

string AbstractFile::readSome(int len) {
    //stringstream meh;

    //return meh;
}

int AbstractFile::size() {
    return 0;
}

