#pragma once

#include "pch.h"

using namespace std;

class Transform {
public:
    Transform(cv::Mat image) {
        this->image = image.clone();
    }

    ~Transform() {
        image.release();
    }

public:
    void Image_to_TXT(string path, unsigned int X = 0, unsigned int Y = 0, double thresh = 200);

private:
    cv::Mat Ini_Image();

    void resize(cv::Mat &mat, unsigned int X = 0, unsigned int Y = 0);

    void sweep_blank(cv::Mat &img, double thresh = 200, double maxval = 255, int type = cv::THRESH_BINARY);

private:
    cv::Mat image;
};