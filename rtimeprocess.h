#ifndef RTIMEPROCESS_H
#define RTIMEPROCESS_H

#include <iostream>
#include <vector>
#include <QString>

#include <opencv2/opencv.hpp>


class rtimeprocess
{
public:
    rtimeprocess();

    void openmovie(QString filename);
    void rtime();

private:

    cv::VideoCapture cap;
    int videoTotalFrames, videorate, videowidth, videoheight;
    int framenum;

    std::vector <cv::Mat> frameAquision;
    std::vector <cv::Mat> Bframe, Gframe, Rframe;




};

#endif // RTIMEPROCESS_H
