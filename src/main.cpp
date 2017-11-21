#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int histshow(Mat Circ);
Mat getHistImg(const MatND& hist);

int main(void)
{
    Mat src = imread("./testpic.png");
    namedWindow("frame", 1); 
    imshow("frame", src);
    cv::waitKey(1);
    histshow(src);

    return 0;
}

int histshow(Mat Circ)
{
    const int channels[1]={0};
    const int histSize[1]={256};
    float hranges[2]={0,255};
    const float* ranges[1]={hranges};
    MatND hist;
    calcHist(&Circ, 1, channels, Mat(), hist, 1, histSize, ranges);
    Mat histImg = getHistImg(Circ);
    namedWindow("Hist",1);
    imshow("Hist", histImg);
    cv::waitKey(1);
    return 0;
}
Mat getHistImg(const MatND& hist)
{
    double maxVal=0;
    double minVal=0;

    //找到直方图中的最大值和最小值
    minMaxLoc(hist,&minVal,&maxVal,0,0);
    int histSize = hist.rows;
    Mat histImg(histSize,histSize,CV_8U,Scalar(255));
    // 设置最大峰值为图像高度的90%
    int hpt=static_cast<int>(0.9*histSize);

    for(int h=0;h<histSize;h++)
    {
        float binVal=hist.at<float>(h);
        int intensity=static_cast<int>(binVal*hpt/maxVal);
        line(histImg,Point(h,histSize),Point(h,histSize-intensity),Scalar::all(0));
    }

    return histImg;
}

