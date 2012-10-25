/*
 * File:   InputStream.h
 * Author: gerjo
 *
 * Created on September 17, 2012, 6:50 PM
 */

#ifndef INPUTSTREAM_H
#define	INPUTSTREAM_H

#include <iostream>
#include <time.h>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#endif

#include "SocketException.h"
#include "../common/CompileConfig.h"

namespace yaxl {
    namespace socket {

        using namespace std;

        class Socket;

        class LIBEXPORT InputStream {
        public:
            InputStream(Socket& socket);
            char read(void);
            string read(const int bytes);
            int available(void);
            void skip(const int amount);

        private:
            InputStream(const InputStream& orig);
            Socket& socket;
            deque<char> buffer;

            void concatToBuffer(char* otherBuffer, const int len);

            const int calculateReadLimit(const int requestSize);
            char shiftBuffer(void);
        };
    }
}

#endif	/* INPUTSTREAM_H */

