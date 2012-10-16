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
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <windows.h>

	#pragma comment(lib, "Ws2_32.lib")

#else
	#include <unistd.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

#ifndef MSG_NOSIGNAL
	#define MSG_NOSIGNAL 0
#endif

namespace yaxl {
namespace socket {

class OutputStream;
class InputStream;

using namespace std;

class Socket {
public:
    Socket(string address, string port);
    virtual ~Socket();
    void close(void);

    OutputStream& getOutputStream(void) const;
    InputStream& getInputStream(void) const;

    friend class OutputStream;
    friend class InputStream;

	const bool isConnected(void);

    friend class ServerSocket;
private:
	Socket(const Socket& orig);
    string address;
    string port;
    int socketFd;
    bool _isConnected;

    void init(void);
    OutputStream* outputStream;
    InputStream* inputStream;

    const int getSocketFd() const;
    void close(const int whom);

    static void setupWGA(void);
};

}
}

#endif	/* SOCKET_H */

