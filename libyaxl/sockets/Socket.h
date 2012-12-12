#ifndef SOCKET_H
#define	SOCKET_H

#ifndef WIN32
	#include <unistd.h>
	#include <netdb.h>
	#include <netinet/in.h>
    #include <netinet/tcp.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

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
    Socket(const string& address, const string& port);
    Socket(const string& address, int port);
    virtual ~Socket();
    void close(void);

    OutputStream& getOutputStream(void) const;
    InputStream& getInputStream(void) const;

    friend class OutputStream;
    friend class InputStream;

	bool isConnected(void);
    void setTcpNoDelay(bool newState);
    void setTcpCork(bool newState);

    const string& getIpv4();
    int getPort();

    friend class ServerSocket;

    int getFd();
private:
    const char yes;
    const char no;

	Socket(const Socket& orig);
    Socket(int socketFd, const string& address, int port);
    string address;
    string port;
    int socketFd;
    bool _isConnected;

    void connect(void);
    OutputStream* outputStream;
    InputStream* inputStream;

    void createStreams(void);
    int getSocketFd() const;
    void close(const int whom);

    static void setupWGA(void);
};

}
}

#endif	/* SOCKET_H */

