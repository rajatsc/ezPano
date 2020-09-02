#ifndef _FRAME_H
#define _FRAME_H


#include <opencv2/core/core.h>

namespace ezPano{


struct Frame{
public:
	cv::Mat img;
		
	//getters
	unsigned int get_frameID();
	double get_time();
	
	//setters
	void set_frameID();
	double set_time();

private:
	unsigned int frameID;
	double time;
	
};


} //namespace ezPano

#endif
