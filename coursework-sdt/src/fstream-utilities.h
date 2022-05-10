#ifndef FSTREAM_UTILITIES_H
#define FSTREAM_UTILITIES_H


#include <fstream>
#include <string>


std::string readStringFromIfstream(std::ifstream&);
bool readBoolFromIfstream(std::ifstream&);
void writeStringInOfstream(std::ofstream&, const std::string&);
void writeBoolInOfstream(std::ofstream&, const bool&);


#endif