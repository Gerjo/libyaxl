#include "Socket.h"

#include "OutputStream.h"
#include "InputStream.h"

namespace yaxl {
namespace socket {

Socket::Socket(string address, string port) : _isConnected(false) {
    this->address = address;
    this->port    = port;

    outputStream  = new OutputStream(*this);
    inputStream   = new InputStream(*this);

    init();
}

Socket::Socket(const Socket& orig) : _isConnected(false) {

}

Socket::~Socket() {
    if(isConnected()) {
		this->close();
	}
}

void Socket::init(void) {

	if(isConnected()) {
		cout << "already connected!";
		exit(6);
	}

	#ifdef WIN32
		WSADATA wsaData;
		if (::WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
			fprintf(stderr, "WSAStartup failed.\n");
			exit(1);
		}
	#endif

	addrinfo hints, *servinfo;
    ::memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (::getaddrinfo(address.c_str(), port.c_str(), &hints, &servinfo) != 0) {
		perror("cannot get addr info.");
        return;
    }

    // loop through all the results and connect to the first we can
    for(addrinfo* p = servinfo; p != 0; p = p->ai_next) {
        if ((socketFd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (::connect(socketFd, p->ai_addr, p->ai_addrlen) == -1) {
            this->close(socketFd);
            perror("client: connect");
            continue;
        }

		// We've reached this point, so all is good.

		char s[32]; // wrong length!
		::inet_ntop(p->ai_family, &(((sockaddr_in*)(sockaddr *)p->ai_addr)->sin_addr), s, sizeof(s));
		printf("client: connecting to %s\n", s);

		_isConnected = true;
        break;
    }

	::freeaddrinfo(servinfo);

    if (!isConnected()) {
        perror("client: failed to connect\n");
        return;
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

}
}
