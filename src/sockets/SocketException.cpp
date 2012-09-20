/* 
 * File:   SocketException.cpp
 * Author: gerjo
 * 
 * Created on September 18, 2012, 10:50 PM
 */

#include "SocketException.h"

SocketException::SocketException(string error) : error(error){
}

SocketException::SocketException(const SocketException& orig) {
    this->error = orig.error;
}

SocketException::~SocketException() throw() {
}

const char* SocketException::what() const throw() {
    return error.c_str();
}