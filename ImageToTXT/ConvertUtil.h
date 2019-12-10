#pragma once

#include "pch.h"

class ConvertUtil {
public:
    static ConvertUtil* getInstance();

    char getChar(uchar key);

private:
    ConvertUtil() {}

private:
    static ConvertUtil *convertUtil;

    std::unordered_map<uchar, char> mapper = {
        {0,'@'},{1,'%'},{2,'#'},{3,'F'},{4,'A'},{5,'H'},{6,'I'},
        {7,'('},{8,';'},{9,'.'},{10,' '}
    };
};
