#include "iostream"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

int main()
{
    std::string path = "E:/jhm files/modelcar/sample.mp4";

    cv::VideoCapture cap(path);
//	VideoCapture cap(0);读取设备摄像头
    cv::Mat img;
    cv::Mat imgGray;
    cv::Mat edges;
    while(true)
    {
        cap.read(img);

        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
        cv::Canny(imgGray, edges, 50, 150); // 设置高低阈值
        imshow("image", img);
        imshow("imageGray", imgGray);
        cv::imshow("Canny Edges", edges);
        cv::waitKey(10);

    }
}