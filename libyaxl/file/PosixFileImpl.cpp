#include "PosixFileImpl.h"

#ifndef WIN32

namespace yaxl {
namespace file {

PosixFileImpl::PosixFileImpl(string path) : AbstractFile(path) {

}

PosixFileImpl::~PosixFileImpl() {

}


bool PosixFileImpl::isDirectory(void) {

    if (loadStat() == 0 && (statDetails.st_mode & S_IFMT) == S_IFDIR) {
        return true;
    }

    return false;
}

int PosixFileImpl::loadStat(void) {
    return stat(_path.c_str(), &statDetails);
}

bool PosixFileImpl::isFile(void) {

    if(loadStat() == 0 && !((statDetails.st_mode & S_IFMT) == S_IFDIR)) {
        return true;
    }

    return false;
}

bool PosixFileImpl::exists(void) {
    return loadStat() == 0;
}

long PosixFileImpl::lastModified(void) {
    return 0;
}

vector<string> PosixFileImpl::list(void) {
    vector<string> files;

    DIR *dp;
    struct dirent *dirp;
    if((dp = ::opendir(_path.c_str())) == 0) {
        throw FileException("Unable to open directory.");
    }

    while ((dirp = ::readdir(dp)) != NULL) {
        if(::strncmp(dirp->d_name, ".", 2) == 0 || ::strncmp(dirp->d_name, "..", 3) == 0) {
            continue;
        }

        files.push_back(string(dirp->d_name));
    }

    ::closedir(dp);

    return files;

}

vector<File> PosixFileImpl::listFiles() {
    vector<string> names = list();
    vector<File> files;

    for(vector<string>::iterator it = names.begin(); it != names.end(); ++it) {
        File tmp(getCanonicalName() + "/" + *it);
        files.push_back(tmp);
    }

    return files;
}


int PosixFileImpl::size() {
    //loadStat();
    //return statDetails.st_size;

    return AbstractFile::size();
}


void PosixFileImpl::mkDir(const string& dirName) {
    mkdir(dirName.c_str(), 0775);
}

}
}

#endif  /* !WIN32 */