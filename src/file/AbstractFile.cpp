#include "AbstractFile.h"


AbstractFile::AbstractFile(string path) : _path(path) {

}

AbstractFile::~AbstractFile() {

}

string AbstractFile::getName() {
	return _path;
}