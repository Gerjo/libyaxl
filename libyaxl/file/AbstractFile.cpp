#include "AbstractFile.h"
#include "FileException.h"

namespace yaxl {
namespace file {

AbstractFile::AbstractFile(string path) : _path(path) {
    _inputFileStream  = 0;
}

AbstractFile::~AbstractFile() {
    closeStreams();
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
    char* memblock = new char[length];

    _inputFileStream->read(memblock, length);

	string str(memblock, length);

	delete[] memblock;

    return str;
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

    char* memblock = new char[length];

    _inputFileStream->read(memblock, limit);

	string str(memblock, limit);

	delete[] memblock;

    return str;
}

int AbstractFile::size() {
    openInputFileStream();

    // Take note of the current internal pointer offset:
    std::streamoff pointerPos = _inputFileStream->tellg();

    _inputFileStream->seekg(0, ios::end);
    std::streamoff fileSize = _inputFileStream->tellg();

    // Restore the internal pointer.
    _inputFileStream->seekg(pointerPos, ios::beg);

    return static_cast<int>(fileSize);
}

void AbstractFile::closeStreams(void) {
    if(_inputFileStream != 0) {
        _inputFileStream->sync();
        _inputFileStream->close();
        delete _inputFileStream;
    }
}

void AbstractFile::openInputFileStream(bool createFile) {
    bool fileExists = false;

    if(!createFile && !(fileExists = isFile())) {
        throw FileException("Cannot open '" + _path + "' for reading. No such file. ");
    }

    // Neither "ifstream" nor "fstream" will create files.
    if(createFile && !fileExists) {
        ofstream writestream(_path.c_str());
        writestream.close();
    }

    if(_inputFileStream == 0) {
        _inputFileStream = new ifstream(_path.c_str(), ios::in | ios::binary);
    }
}

int AbstractFile::getRemainingSize() {
    int size  = this->size();
    std::streamoff pntr = _inputFileStream->tellg();
    std::streamoff delta = size - pntr;

    return static_cast<int>(delta);
}

string AbstractFile::computeMD5(void) {
    openInputFileStream();

    // Take note of the pointer, and then reset it.
    std::streamoff pointer = _inputFileStream->tellg();
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
        throw FileException("Cannot open '" + _path + "' for writing. No such file. ");
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

void AbstractFile::mkDir() {
    mkDir(_path);
}

void AbstractFile::mkDirs() {
    if(!isDirectory()) {

        stringstream ss(getCanonicalName());
        string folder;
        string path;
        while(std::getline(ss, folder, '/')) {

            // If the user creates a path like foo///meh//bar// the extra
            // slashes will be skipped. In reality "getCanonicalName" should
            // do this though.
            if(folder.length() == 0) {
                continue;
            }

            mkDir(path += folder + "/");
        }
    }
}

bool AbstractFile::remove(void) {

    if(exists()) {
        closeStreams();

        return ::remove(_path.c_str()) == 0;
    }

    return false;
}

}
}