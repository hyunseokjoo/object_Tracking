#include <iostream>				
#include <stdio.h>              
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>         
#include <opencv2/highgui.hpp>		
#include <opencv2/imgproc.hpp>      
#include <opencv2/videoio.hpp>
#include <opencv2/tracking.hpp>


using namespace cv;
using namespace std;

int main(int ac, char** av) {
	cv::VideoCapture cap("video/coffee.mp4");
	cv::VideoWriter videoWriter;
	cv::Mat videoFrame;
	cv::Mat select_ROI;

	if (!cap.isOpened()) return 0;

	float videoFPS = cap.get(cv::CAP_PROP_FPS);
	cv::Ptr<cv::Tracker> trac = cv::TrackerCSRT::create();
	cap.read(videoFrame);
	cv::Rect2d roi = cv::selectROI("Select ROI", videoFrame, false);
	destroyWindow("Select ROI");

	trac -> init(videoFrame, roi);

	while (cap.read(videoFrame))
	{
		
		if (trac->update(videoFrame, roi)) {
			select_ROI = videoFrame(Range(roi.y, roi.y + roi.height), Range(roi.x, roi.x + roi.width));
			cv::rectangle(videoFrame, roi, cv::Scalar(255, 0, 0), 2, 8);
		}

		videoWriter << select_ROI;
		cv::imshow("select_ROI", select_ROI);
		cv::imshow("video", videoFrame);
		if (cv::waitKey(1000/ videoFPS) == 27) break;
	};
	 

	cap.release();
	destroyAllWindows;

	return 0;
}

