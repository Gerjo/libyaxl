#include "AbstractFile.h"

namespace yaxl {
namespace file {

AbstractFile::AbstractFile(string path) : _path(path) {
    _inputFileStream  = 0;
}

AbstractFile::~AbstractFile() {
    if(_inputFileStream != 0) {
        _inputFileStream->sync();
        _inputFileStream->close();
        delete _inputFileStream;
    }
}

string AbstractFile::getName() {
	return _path;
}

string AbstractFile::getCanonicalName() {
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
    openInputFileStream();

    const int length = getRemainingSize();
    char memblock[length];

    _inputFileStream->read(memblock, length);

    return string(memblock, length);
}

string AbstractFile::readLine(const char& delimiter) {
    openInputFileStream();

    string asString;

    std::getline(*_inputFileStream, asString, delimiter);

    return asString;
}

string AbstractFile::readLine() {
    return readLine('\n');
}

string AbstractFile::readSome(int len) {
    openInputFileStream();

    int length = getRemainingSize();
    int limit  = min(len, length);

    char memblock[length];

    _inputFileStream->read(memblock, limit);

    return string(memblock, limit);
}

int AbstractFile::size() {
    openInputFileStream();

    // Take note of the current internal pointer offset:
    const int pointerPos = _inputFileStream->tellg();

    _inputFileStream->seekg(0, ios::end);
    int fileSize = _inputFileStream->tellg();

    // Restore the internal pointer.
    _inputFileStream->seekg(pointerPos, ios::beg);

    return fileSize;
}

void AbstractFile::openInputFileStream(bool createFile) {
    if(!createFile && !isFile()) {
        cout << " cannot open '" << _path << "' for reading. no such file. " << endl;
        cout << "isFile?" << (int) isFile() << " createFile?" << createFile << endl;
        exit(23);
    }

    if(_inputFileStream == 0) {
        _inputFileStream = new ifstream(_path.c_str(), ios::in | ios::binary);
    }
}

int AbstractFile::getRemainingSize() {
    int size  = this->size();
    int pntr  = _inputFileStream->tellg();
    int delta = size - pntr;

    return delta;
}

string AbstractFile::computeMD5(void) {
    openInputFileStream();

    // Take note of the pointer, and then reset it.
    int pointer = _inputFileStream->tellg();
    reset();
    MD5 md5(readAll());

    // Restore the pointer:
    _inputFileStream->seekg(pointer, ios::beg);

    return md5.hexdigest();
}

void AbstractFile::reset() {
    if(_inputFileStream != 0) {
        _inputFileStream->seekg(0, ios::beg);
    }
}

void AbstractFile::write(const string& data) {
    this->write(data.c_str(), data.length());
}

void AbstractFile::write(const char* data, const int length) {
    if(!isFile()) {
        cout << "exception: cannot write to non existing file." << endl;
        return;
    }

    ofstream writer(_path.c_str(), ios::out);
    writer.write(data, length);
    writer.flush();
}

void AbstractFile::append(const string& data) {
    this->append(data.c_str(), data.length());
}

void AbstractFile::append(const char* data, const int length) {
    ofstream writer(_path.c_str(), ios::out | ios::app);
    writer.write(data, length);
    writer.flush();
}

bool AbstractFile::createNewFile() {
    if(!isDirectory()) {
        if(!isFile()) {
            // Opening an input stream, with the "true" flag set to force
            // the creation of a file.
            openInputFileStream(true);
            return true;
        }
    }

    return false;
}

}
}