#include "AbstractFile.h"


AbstractFile::AbstractFile(string path) : _path(path) {
    _inputFileStream  = 0;
    _outputFileStream = 0;
}

AbstractFile::~AbstractFile() {
    if(_inputFileStream != 0) {
        _inputFileStream->close();
        delete _inputFileStream;
    }

    if(_outputFileStream != 0) {
        _outputFileStream->close();
        delete _outputFileStream;
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
        _inputFileStream = new ifstream();
        _inputFileStream->open(_path.c_str(), ios::in | ios::binary);

        reset();
    }
}

void AbstractFile::openOutputFileStream(bool createFile) {
    if(!createFile && !isFile()) {
        cout << " cannot open '" << _path << "' for writing. no such file. " << endl;
        exit(23);
    }

    if(_outputFileStream == 0) {
        _outputFileStream = new ofstream();
        _outputFileStream->open(_path.c_str(), ios::out | ios::binary);
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

    int pointer = _inputFileStream->tellg();
    reset();
    MD5 md5(readAll());

    _inputFileStream->seekg(pointer, ios::beg);

    return md5.hexdigest();
}

void AbstractFile::reset() {
    if(_inputFileStream != 0) {
        _inputFileStream->seekg(0, ios::beg);
    } else {
        // exception! :(
    }
}

void AbstractFile::write(const string& data) {
    openOutputFileStream();

    _outputFileStream->write(data.c_str(), data.length());
}

void AbstractFile::write(char* data, const int length) {
    openOutputFileStream();

    _outputFileStream->write(data, length);
}

bool AbstractFile::createNewFile() {
    if(!isDirectory()) {
        if(!isFile()) {
            openOutputFileStream(true);
            return true;
        }
    }

    return false;
}