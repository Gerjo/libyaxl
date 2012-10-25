#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <ws2tcpip.h>
#endif

#include "Socket.h"

#include "OutputStream.h"
#include "InputStream.h"

namespace yaxl {
namespace socket {

Socket::Socket(const string& address, const string& port) : _isConnected(false), yes(1), no(0) {
    this->address.append(address.c_str());
    this->port.append(port.c_str());

    createStreams();
    connect();
}

Socket::Socket(string address, int port) : _isConnected(false), yes(1), no(0) {
    stringstream ss;
    ss << port;

    this->address = address;
    this->port    = ss.str();

    createStreams();
    connect();
}

// Private, available via friendclass.
Socket::Socket(int socketFd) : yes(1), no(0)  {
    this->socketFd = socketFd;
    _isConnected   = true;
    createStreams();
}

Socket::Socket(const Socket& orig) : _isConnected(false), yes(1), no(0)  {
    throw SocketException("Sockets cannot be copied.");
}

Socket::~Socket() {
    if(isConnected()) {
		this->close();
	}

    delete outputStream;
    delete inputStream;
}

int Socket::getFd() {
    return socketFd;
}

void Socket::setTcpNoDelay(bool newState) {
    const char& newFlag = newState ? yes : no;

    if(setsockopt(socketFd, IPPROTO_TCP, TCP_NODELAY, &newFlag, sizeof(int)) < 0) {
        throw SocketException(strerror(errno));
    }
}

void Socket::setTcpCork(bool newState) {
    const char& newFlag = newState ? yes : no;

    // TCP_CORK does not exist on Windows.
#ifndef _WIN32
    if(setsockopt(socketFd, IPPROTO_TCP, TCP_CORK, &newFlag, sizeof(int)) < 0) {
        throw SocketException(strerror(errno));
    }
#else
    std::string error("Not implemented on the Windows platforms.");
    throw SocketException(error);
#endif
}

void Socket::createStreams(void) {
    outputStream  = new OutputStream(*this);
    inputStream   = new InputStream(*this);
}

void Socket::connect(void) {

	if(isConnected()) {
        throw SocketException("Socket is already connected.");
	}

    Socket::setupWGA();

	addrinfo hints, *servinfo;
    ::memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (::getaddrinfo(address.c_str(), port.c_str(), &hints, &servinfo) != 0) {
        throw SocketException("Unable to acquire addrinfo.");
    }

    // Iterate through all the results and connect to the first one that lets
    // us actually connect. Nb: This accounts for DNS a-records with multiple
    // records associated with them.
    for(addrinfo* p = servinfo; p != 0; p = p->ai_next) {
        if ((socketFd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            throw SocketException(strerror(errno));
        }


        if (::connect(socketFd, p->ai_addr, p->ai_addrlen) == -1) {
            // So we're unable to connect. Not detrimental, since there may
            // be more addresses to try.
            this->close(socketFd);
            continue;
        }

		// We've reached this point, so all is good.

		char s[32]; // wrong length!
		::inet_ntop(p->ai_family, &(((sockaddr_in*)(sockaddr *)p->ai_addr)->sin_addr), s, sizeof(s));
		printf("client: connected to %s\n", s);

		_isConnected = true;
        break;
    }

	::freeaddrinfo(servinfo);

    if (!isConnected()) {
        throw SocketException("Unable to connect.");
    }
}

OutputStream& Socket::getOutputStream(void) const {
    return *outputStream;
}

InputStream& Socket::getInputStream(void) const {
    return *inputStream;
}

const int Socket::getSocketFd() const {
    return socketFd;
}

void Socket::close(void) {
	this->close(socketFd);
}

void Socket::close(const int whom) {
	#ifdef WIN32
		::closesocket(whom);
	#else
		::close(whom);
	#endif

	_isConnected = false;
}

const bool Socket::isConnected(void) {
	return _isConnected;
}


void Socket::setupWGA(void) {
	#ifdef WIN32
        // TODO: can/should this be a singleton?
		WSADATA wsaData;
		if (::WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
			fprintf(stderr, "WSAStartup failed.\n");
			exit(1);
		}
	#endif
}

}
}
