#include "stitching.h"

#include <iostream>

namespace ezPano{

stitching::stitching(){

}

stitching::~stitching(){

}

void stitching::run(){
	while(true){
		
		if (terminate_is_requested()){
			terminate();
			break;
		}
		


		//std::cout << "stitching" << std::endl;
	}
}

/*
void stitching::find_correspondences(){
	//loop over the features_db
		
}
*/


void stitching_calculate_overlap(){
	//finds the overlap between the mosaic and current keyframe

}


//pause and resume
void stitching::request_pause(){

}

void stitching::is_paused() const{

}

void stitching::resume(){

}


//terminate
void stitching::request_terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_terminate_is_requested = true;
}

bool stitching::is_terminated() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_is_terminated;
}

bool stitching::terminate_is_requested() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_terminate_is_requested;
}

void stitching::terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_is_terminated = true;
}

}
