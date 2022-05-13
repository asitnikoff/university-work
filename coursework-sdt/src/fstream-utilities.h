#ifndef FSTREAM_UTILITIES_H
#define FSTREAM_UTILITIES_H


#include <fstream>
#include <string>

#include "products.h"


std::string readStringFromIfstream(std::ifstream&);
bool readBoolFromIfstream(std::ifstream&);
DateProperties readDateFromIfstream(std::ifstream&);
int readIntFromIfstream(std::ifstream&);
void writeStringInOfstream(std::ofstream&, const std::string&);
void writeBoolInOfstream(std::ofstream&, const bool&);
void writeDateInOfstream(std::ofstream&, const DateProperties&);
void writeIntInOfstream(std::ofstream&, const int&);


#endif