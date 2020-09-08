#ifndef TRACKING_H
#define TRACKING_H

//standard
#include <mutex>
#include <vector>

//opencv
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

//local
#include "bufferQueue.h"
#include "stitching.h"


namespace ezPano{

//tracker state
enum class tracker_state{
	NOT_INITIALIZED,
	INITIALIZING,
	TRACKING,
	LOST
};



class tracking{
public:

	tracking();
	~tracking();
	void run();


	//buffer queue stuff
	void queue_image(cv::Mat& img);
	size_t get_num_queued_images() const;
	bool image_is_queued();

	//pause and resume
	void request_pause();
	bool is_paused() const;
	void resume();
	
	//terminate
	void request_terminate();
	bool is_terminated() const;
	

private:
	//buffer queue of images
	bufferQueue<cv::Mat> img_bq;
	bool image_is_queued() const;

	// last image
	cv::Mat last_img;
	//std::vector<cv::KeyPoint> last_keypoint;
	cv::Mat last_descriptors;
	
	// current image
	cv::Mat curr_img;
	//std::vector<cv::keyPoint> curr_keypoint;
	cv::Mat curr_descriptors;
	
	// feature detector and matcher
	std::unique_ptr<cv::Feature2D> detector;
	std::unique_ptr<cv::DescriptorMatcher> matcher;
	
	// matches
	std::vector<std::vector<cv::DMatch>> matches;
		
	//pointer to stitcher
	stitching* m_stitcher;


	//pause
	mutable std::mutex m_mtx_pause;
	bool m_is_paused = false;
	bool m_pause_is_requested = false;

	//terminate
	mutable std::mutex m_mtx_terminate;
	bool m_is_terminated = false;
	bool m_terminate_is_requested = false; 	
	bool terminate_is_requested() const;
	void terminate();

};

} //namespace ezPano

#endif
