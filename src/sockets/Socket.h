#ifndef SOCKET_H
#define	SOCKET_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sstream>
#include <cstdio>

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
    #include <sys/fcntl.h>
    #include <sys/ioctl.h>
	#include <arpa/inet.h>
#endif

#ifndef MSG_NOSIGNAL
	#define MSG_NOSIGNAL 0
#endif

#include "SocketException.h"

class OutputStream;
class InputStream;

using namespace std;

class Socket {
public:
    Socket(string address, int port) throw();
    Socket(string address, string port) throw();
    virtual ~Socket();
    void close(void);

    OutputStream& getOutputStream(void) const;
    InputStream& getInputStream(void) const;

    friend class OutputStream;
    friend class InputStream;

	const bool isConnected(void);

    int nextReadSize(void);

private:
	Socket(const Socket& orig);
    string address;
    string port;
    int socketFd;
    bool _isConnected;

    void init(void) throw();
    OutputStream* outputStream;
    InputStream* inputStream;

    const int getSocketFd() const;
    void close(const int whom);
};

#endif	/* SOCKET_H */

