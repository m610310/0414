#include "rtimeprocess.h"

rtimeprocess::rtimeprocess()
{
}

void rtimeprocess::openmovie(QString filename)
{
    if(cap.isOpened()){
        cap.release();
    }
    if(!cap.isOpened()){
        cap.open(filename.toStdString());
    }
    if(cap.isOpened()){

        videoTotalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
        videorate = cap.get(CV_CAP_PROP_FPS);

        videowidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        videoheight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        std::cout << "videoinfo get" << std::endl;


        frameAquision.resize(videoTotalFrames + 1);
        Bframe.resize(videoTotalFrames + 1);
        Gframe.resize(videoTotalFrames + 1);
        Rframe.resize(videoTotalFrames + 1);

        std::cout << "vector resize" << std::endl;

        cv::Mat tmpframe;
        std::vector <cv::Mat> tmpchannels;
        tmpchannels.resize(3);

        std::cout << "channels resize" << std::endl;


        for(int framenum = 0; framenum < videoTotalFrames; framenum ++){

            cap.set(CV_CAP_PROP_POS_FRAMES, framenum);

            cap >> tmpframe;

            frameAquision[framenum] = tmpframe;

            std::cout << "tmpframe get" << std::endl;

            cv::split(tmpframe, tmpchannels);

            Bframe[framenum] = tmpchannels[0];
            Gframe[framenum] = tmpchannels[1];
            Rframe[framenum] = tmpchannels[2];

            std::cout << "BGRframe set" << std::endl;

            cv::imshow ("tmpframe", tmpframe);
            cv::imshow ("Rframe", Rframe[framenum]);




        }
    }
}

void rtimeprocess::rtime()
{
    std::vector <cv::Mat> Rhosonaga;
    Rhosonaga.resize(videoTotalFrames + 1);

    cv::Mat Rconcat;

    for(int framenum = 0; framenum < videoTotalFrames; framenum ++){

        cv::reduce(Rframe[framenum], Rhosonaga[framenum], 1, CV_REDUCE_AVG);

        if(framenum == 0){
            Rconcat = Rhosonaga[0];
        }
        else if(framenum > 0){
            cv::hconcat(Rconcat, Rhosonaga[framenum], Rconcat);
        }
    }

    cv::imshow("Rtime", Rconcat);
}











