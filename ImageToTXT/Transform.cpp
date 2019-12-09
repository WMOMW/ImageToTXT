#include "pch.h"

void Transform::Image_to_TXT(string path, unsigned int X, unsigned int Y, double thresh) {
    resize(image, X, Y);
    // cv::GaussianBlur(image, image, cv::Size(5, 5), 3);
    sweep_blank(image, thresh);
    //cv::imshow("1", image);
    //cv::waitKey();
    ofstream out;
    out.open(path);
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            switch (image.at<uchar>(i, j) / 25) {
            case 0:
                out << '@';
                break;
            case 1:
                out << '%';
                break;
            case 2:
                out << '#';
                break;
            case 3:
                out << 'F';
                break;
            case 4:
                out << 'A';
                break;
            case 5:
                out << 'H';
                break;
            case 6:
                out << 'I';
                break;
            case 7:
                out << '(';
                break;
            case 8:
                out << ';';
                break;
            case 9:
                out << '.';
                break;
            default:
                out << ' ';
                break;
            }
        }
        out << endl;
    }
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