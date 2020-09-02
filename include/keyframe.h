#ifndef _KEYFRAME_H
#define _KEYFRAME_H

#include <mutex> 

#include <opencv2/core/core.hpp>

namespace ezPano{

class keyframe{
public:
	keyframe();
	~keyframe();

protected:
	cv::Mat homography;
	

	//keypoint in global coordinate
	//std::vector<cv::Point2f>


	//3D information ? maybe



};

} //namespace ezPano


#endif
