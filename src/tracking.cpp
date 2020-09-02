#include "tracking.h"

#include <iostream>

namespace ezPano{

//constructor
tracking::tracking()
:bq(10)
{

}


//destructor
tracking::~tracking(){

}


//main tracking loop
void tracking::run(){
	while(true){
		
		if (terminate_is_requested()){
			terminate();
			break;
		}
		
		
		//std::cout << "tracking" << std::endl;
	}
}


//------------------------------------------------------------//
//                buffer queue stuff
//------------------------------------------------------------//

//queue the image
void tracking::queue_image(cv::Mat& img){
	bq.push(img);	
}


//get the number of queued keyframes
size_t tracking::get_num_queued_images() const{
	return bq.size();
}	


//check if image is queued
bool tracking::image_is_queued() const{
	return !bq.empty();
}


//pause
void tracking::request_pause(){

}

void tracking::is_paused() const{

}

void tracking::resume(){

}


//terminate tracking process
void tracking::request_terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_terminate_is_requested = true;
}

bool tracking::is_terminated() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_is_terminated;
}

bool tracking::terminate_is_requested() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_terminate_is_requested;
}

void tracking::terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_is_terminated = true;
}

} //namespace ezPano
