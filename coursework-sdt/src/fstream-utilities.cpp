#include <fstream>

#include "fstream-utilities.h"


std::string readStringFromIfstream(std::ifstream& fin) {
    int len;
    fin.read((char*)&len, sizeof(int));
    char* temp = new char[len + 1];
    fin.read(temp, len);
    temp[len] = '\0';
    std::string result = temp;
    delete[] temp;

    return result;
}

bool readBoolFromIfstream(std::ifstream& fin) {
    bool flag;
    fin.read((char*)&flag, sizeof(bool));

    return flag;
    return flag;
}

void writeStringInOfstream(std::ofstream& fout, const std::string& str) {
    int len = (int)str.size();
    fout.write((char*)&len, sizeof(int));
    fout.write(str.c_str(), len);
}

void writeBoolInOfstream(std::ofstream& fout, const bool& flag) {
    fout.write((char*)&flag, sizeof(bool));
}
