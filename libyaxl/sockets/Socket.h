#ifndef SOCKET_H
#define	SOCKET_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#ifdef WIN32
	#include <ws2tcpip.h>
#else
	#include <unistd.h>
	#include <netdb.h>
	#include <netinet/in.h>
    #include <netinet/tcp.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

#include "../common/CompileConfig.h"

#ifndef MSG_NOSIGNAL
	#define MSG_NOSIGNAL 0
#endif

namespace yaxl {
namespace socket {

class OutputStream;
class InputStream;

using namespace std;

class LIBEXPORT Socket {
public:
    Socket(string address, string port);
    Socket(string address, int port);
    virtual ~Socket();
    void close(void);

    OutputStream& getOutputStream(void) const;
    InputStream& getInputStream(void) const;

    friend class OutputStream;
    friend class InputStream;

	const bool isConnected(void);
    void setTcpNoDelay(bool newState);
    void setTcpCork(bool newState);

    friend class ServerSocket;
private:
    const char yes;
    const char no;

	Socket(const Socket& orig);
    Socket(int socketFd);
    string address;
    string port;
    int socketFd;
    bool _isConnected;

    void connect(void);
    OutputStream* outputStream;
    InputStream* inputStream;

    void createStreams(void);
    const int getSocketFd() const;
    void close(const int whom);

    static void setupWGA(void);
};

}
}

#endif	/* SOCKET_H */

