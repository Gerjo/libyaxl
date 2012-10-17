/*
 * File:   OutputStream.h
 * Author: gerjo
 *
 * Created on September 17, 2012, 6:30 PM
 */

#ifndef OUTPUTSTREAM_H
#define	OUTPUTSTREAM_H

#include <string>
#include <sstream>

#ifdef WIN32
	#include <winsock2.h>
	#include <windows.h>
#else

#endif

#include "Socket.h"
#include "../CompileConfig.h"

namespace yaxl {
namespace socket {

using namespace std;

class LIBEXPORT OutputStream {
public:
    OutputStream(Socket& socket);
	void write(const stringstream ssToSend);
	void write(const string stringToSend);
    void write(const char* bytes);
    void write(const char* bytes, const int len);

private:
	OutputStream(const OutputStream& orig);
    Socket& socket;
};

}
}

#endif	/* OUTPUTSTREAM_H */

