#include "pch.h"

void Transform::Image_to_TXT(string path, unsigned int X, unsigned int Y, double thresh) {
    resize(image, X, Y);
    // cv::GaussianBlur(image, image, cv::Size(5, 5), 3);
    sweep_blank(image, thresh);
    ConvertUtil *mapper = ConvertUtil::getInstance();
    ofstream out;
    out.open(path);
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            out << mapper->getChar(image.at<uchar>(i, j) / 25);
            cout << mapper->getChar(image.at<uchar>(i, j) / 25);
        }
        out << endl;
        cout << endl;
    }
    out << "\n\n需要在空格与字符宽度相等的文本编辑器下查看" << endl;
    out.close();
}

cv::Mat Transform::Ini_Image() {
    resize(image);
    // cv::GaussianBlur(image, image, cv::Size(5, 5), 3);
    sweep_blank(image);
    return image;
}

void Transform::resize(cv::Mat &mat, unsigned int X, unsigned int Y) {
    if (!X && !Y) {
        if (mat.cols > 120) {
            X = 120;
            Y = static_cast<unsigned int>(mat.rows * (60.0 / mat.cols));
        }
        else {
            X = mat.cols;
            Y = mat.rows / 2;
        }
    }
    else {
        if (!X) {
            X = static_cast<unsigned int>(mat.cols*(Y / static_cast<double>(mat.rows)));
        }
        if (!Y) {
            Y = static_cast<unsigned int>(mat.rows*(X / static_cast<double>(mat.cols))) / 2;
        }
    }
    cv::resize(mat, mat, cv::Size(X, Y));
}

void Transform::sweep_blank(cv::Mat &img, double thresh, double maxval, int type) {
    cv::Mat temp;
    cv::threshold(img, temp, 200, 255, cv::THRESH_BINARY);
    for (int x = temp.cols - 1; x >= 0; --x) {
        for (int y = temp.rows - 1; y >= 0; --y) {
            if (255 == temp.at<char>(cv::Point(x, y))) {
                img.at<char>(cv::Point(x, y)) = (char)255;
            }
        }
    }
}