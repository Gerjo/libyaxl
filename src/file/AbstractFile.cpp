#include "AbstractFile.h"


AbstractFile::AbstractFile(string path) : _path(path) {
    _fileStream = 0;
}

AbstractFile::~AbstractFile() {
    if(_fileStream != 0) {
        _fileStream->close();
        delete _fileStream;
    }
}

string AbstractFile::getName() {
	return _path;
}

string AbstractFile::getCononicalName() {
    string name = getName();
    int len     = name.length();

    while(len > 1 && name.substr(len - 1, len).compare("/") == 0) {
        name = name.substr(0, len -1);
        len  = name.length();
    }

    // Hmmmz:
    //std::remove(name.begin(), name.end(), '/');

    return name;
}


string AbstractFile::readAll() {
    openFileStream();

    const int length = getRemainingSize();
    char memblock[length];

    _fileStream->read(memblock, length);

    return string(memblock, length);
}

string AbstractFile::readLine() {
    openFileStream();

    return "";
}

string AbstractFile::readSome(int len) {
    openFileStream();

    int length = getRemainingSize();
    int limit  = min(len, length);

    char memblock[length];

    _fileStream->read(memblock, limit);

    return string(memblock, limit);
}

int AbstractFile::size() {
    openFileStream();

    // Take note of the current internal pointer offset:
    const int pointerPos = _fileStream->tellg();

    _fileStream->seekg(0, ios::end);
    int fileSize = _fileStream->tellg();

    // Restore the internal pointer.
    _fileStream->seekg(pointerPos, ios::beg);

    return fileSize;
}

void AbstractFile::openFileStream(void) {
    if(_fileStream == 0) {
        _fileStream = new ifstream();
        _fileStream->open(_path.c_str(), ios::in|ios::binary|ios::ate);

        // Reset the internal pointer to the beginning.
        _fileStream->seekg(0, ios::beg);
    }
}


int AbstractFile::getRemainingSize() {
    int size  = this->size();
    int pntr  = _fileStream->tellg();
    int delta = size - pntr;

    return delta;
}