#include "Socket.h"

#include "OutputStream.h"
#include "InputStream.h"

namespace yaxl {
namespace socket {

Socket::Socket(string address, string port) : _isConnected(false) {
    this->address = address;
    this->port    = port;

    createStreams();
    connect();
}

Socket::Socket(string address, int port) : _isConnected(false) {
    stringstream ss;
    ss << port;

    this->address = address;
    this->port    = ss.str();

    createStreams();
    connect();
}

// Private, available via friendclass.
Socket::Socket(int socketFd) {
    this->socketFd = socketFd;
    _isConnected   = true;
    createStreams();
}

Socket::Socket(const Socket& orig) : _isConnected(false) {
    throw SocketException("Sockets cannot be copied.");
}

Socket::~Socket() {
    if(isConnected()) {
		this->close();
	}

    delete outputStream;
    delete inputStream;
}

void Socket::setTcpNoDelay(bool newState) {
    const int& newFlag = newState ? yes : no;

    if(setsockopt(socketFd, IPPROTO_TCP, TCP_NODELAY, (void*) &newFlag, sizeof(newFlag)) < 0) {
        throw SocketException(strerror(errno));
    }
}

void Socket::setTcpCork(bool newState) {
    const int& newFlag = newState ? yes : no;

    if(setsockopt(socketFd, IPPROTO_TCP, TCP_CORK, (void*) &newFlag, sizeof(newFlag)) < 0) {
        throw SocketException(strerror(errno));
    }
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
