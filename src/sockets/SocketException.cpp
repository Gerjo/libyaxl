/*
 * File:   SocketException.cpp
 * Author: gerjo
 *
 * Created on September 18, 2012, 10:50 PM
 */

#include "SocketException.h"

namespace yaxl {
namespace socket {

SocketException::SocketException(string error) : error(error){
}

SocketException::SocketException(const SocketException& orig) {
}

SocketException::~SocketException() {
}

}
}