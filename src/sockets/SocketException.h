/*
 * File:   SocketException.h
 * Author: gerjo
 *
 * Created on September 18, 2012, 10:50 PM
 */

#ifndef SOCKETEXCEPTION_H
#define	SOCKETEXCEPTION_H

#include <exception>
#include <string>

namespace yaxl {
namespace socket {

using namespace std;

class SocketException {
public:
    SocketException(string error);
    SocketException(const SocketException& orig);
    virtual ~SocketException();

	virtual string what() const;
private:
    string error;
};

}
}

#endif	/* SOCKETEXCEPTION_H */

