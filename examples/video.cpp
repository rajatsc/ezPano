#include <chrono>
#include <iostream>
#include "system.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>


int main(int argc, char** argv)
{	
	cv::Mat frame;
	cv::VideoCapture cap;
	cap.open(0);

	while(true){
		cap.read(frame);

		if (frame.empty()) break;

		cv::imshow("Frame", frame);

		char c=(char)cv::waitKey(25);
		if (c==27)
			break;
	}

	cap.release();
	cv::destroyAllWindows();

	return 0;
}
