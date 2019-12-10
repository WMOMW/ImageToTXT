#include "pch.h"

ConvertUtil* ConvertUtil::getInstance() {
    if (convertUtil == nullptr) {
        convertUtil = new ConvertUtil();
    }
    return convertUtil;
}

char ConvertUtil::getChar(uchar key) {
    if (mapper.find(key) == mapper.end()) {
        return ' ';
    }
    return mapper.find(key)->second;
}

ConvertUtil *ConvertUtil::convertUtil = nullptr;