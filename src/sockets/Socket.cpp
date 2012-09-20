#include <string.h>

#include "Socket.h"

#include "OutputStream.h"
#include "InputStream.h"
#include "SocketException.h"


Socket::Socket(string address, int port) throw() {
    stringstream ss;
    ss << port;
    Socket(address, ss.str());
}

Socket::Socket(string address, string port) throw() : _isConnected(false) {
    this->address = address;
    this->port    = port;

    try {
        init();
    } catch(const SocketException &ex) {
        throw;
    }

    outputStream  = new OutputStream(*this);
    inputStream   = new InputStream(*this);
}

Socket::Socket(const Socket& orig) : _isConnected(false) {

}

Socket::~Socket() {
    if(isConnected()) {
		this->close();
	}
}

void Socket::init(void) throw() {

	if(isConnected()) {
        throw SocketException("Socket is already connected.");
	}


	#ifdef WIN32
		WSADATA wsaData;
		if (::WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
			throw new SocketException("WSA cannot startup.");
		}
	#endif

	addrinfo hints, *servinfo;
    ::memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (::getaddrinfo(address.c_str(), port.c_str(), &hints, &servinfo) != 0) {
        throw SocketException("getaddrinfo: Cannot get address info.");
    }

    // loop through all the results and connect to the first we can
    for(addrinfo* p = servinfo; p != 0; p = p->ai_next) {
        if ((socketFd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }

        if (::connect(socketFd, p->ai_addr, p->ai_addrlen) == -1) {
            // Able to open a socket, but cannot connect.
            this->close(socketFd);
            continue;
        }

		// We've reached this point, so all is good.

		_isConnected = true;
        break;
    }

	::freeaddrinfo(servinfo);

    if (!isConnected()) {
        throw SocketException("Unable to connect to client. None of the addresses returned by getaddrinfo() are valid.");
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
    if (!isConnected()) {
        throw SocketException("Cannot close an already closed socket.");
    }

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

int Socket::nextReadSize(void) {

	#ifdef WIN32
		u_long result = -1;
	#else
		long int result = -1;
	#endif

    int status;

    #ifdef WIN32
        status = ioctlsocket(socketFd, FIONREAD, &result);
    #else
        status = ioctl(socketFd, FIONREAD, &result);
    #endif

        cout  << "mehmeh" << endl;

    if(status)
        throw SocketException("Unable to perform ioctl/status");


    return result;
}