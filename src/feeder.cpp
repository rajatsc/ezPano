#include "feeder.h"

#include <stdexcept>
#include <iostream>
#include <thread>

namespace ezPano{

void identity::processImplementation(cv::Mat& img){}


feeder::feeder(int _deviceID = 1, int _frame_skip=1)
	:m_frame_skip(_frame_skip), deviceID(_deviceID)
{
	processor = new identity();
	cap.open(deviceID);

	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
        throw "unable to open camera"; 
    }
}

feeder::~feeder(){}


void feeder::feed(){
	
	unsigned int num_frame = 0;
	while(!is_finished){
			
		if (terminate_is_requested()){
			terminate();
			break;
		}
		
		is_finished = cap.read(img);
		std::cout << "read img" << std::endl;
		if (!img.empty() && (num_frame%m_frame_skip) == 0)
		{
			//m_tracker->queue_image();
		}

		if (!is_finished){
			if (m_pause_is_requested){
				//pause();

				while(is_paused() && !terminate_is_requested()){
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}
			}
		}
		
	}
}

void feeder::pause(){

}

bool feeder::is_paused() const{

}

//terminate tracking process
void feeder::request_terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_terminate_is_requested = true;
}

bool feeder::is_terminated() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_is_terminated;
}

bool feeder::terminate_is_requested() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_terminate_is_requested;
}

void feeder::terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_is_terminated = true;
}
} //namespace ezPano
