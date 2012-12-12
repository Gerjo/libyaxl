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

#ifndef WIN32
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#endif

#include "SocketException.h"
#include "DisconnectException.h"
#include "../common/CompileConfig.h"

namespace yaxl {
    namespace socket {

        using namespace std;

        class Socket;

        class LIBEXPORT InputStream {
        public:
            InputStream(Socket& socket);
            ~InputStream(void);
            char read(void);
            string read(const int bytes);
            int available(void);
            void skip(const int amount);
            void setBlocking(bool isBlocking);
            bool ensureAvailable(int byteCount);
            void forceQuit(void);

        private:
            InputStream(const InputStream& orig);
            Socket& socket;
            deque<char> buffer;
            bool _isBlocking;
            bool _isStopping;

            void concatToBuffer(char* otherBuffer, const int len);

            int calculateReadLimit(const int requestSize);
            char shiftBuffer(void);
        };
    }
}

#endif	/* INPUTSTREAM_H */

