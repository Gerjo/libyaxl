#include "PosixFileImpl.h"

#ifndef WIN32

PosixFileImpl::PosixFileImpl(string path) : AbstractFile(path) {

}

PosixFileImpl::~PosixFileImpl() {

}

// S_ISDIR(st.st_mode); ??
bool PosixFileImpl::isDirectory(void) {
    // Using opendir()
    //return = (::opendir(_path.c_str()) != 0);


    int result = loadStat();

    if (result == 0 && ((statDetails.st_mode & S_IFMT) == S_IFDIR)) {
        return true;
    }

    return false;
}

int PosixFileImpl::loadStat(void) {
    return stat(_path.c_str(), &statDetails);
}

bool PosixFileImpl::isFile(void) {

    if(loadStat() == 0 && !isDirectory()) {
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
        cout << "could not opendir." << endl;
        exit(-1);
    }

    while ((dirp = readdir(dp)) != NULL) {
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
        File tmp(getCononicalName() + "/" + *it);
        files.push_back(tmp);

        cout << "con: " << getCononicalName() << endl;
    }

    return files;
}

#endif  /* !WIN32 */