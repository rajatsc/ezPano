#include "global_optimization.h"

#include <iostream>

namespace ezPano{

global_optimization::global_optimization(){

}


global_optimization::~global_optimization(){

}


void global_optimization::run(){
	while(true){
		if (terminate_is_requested()){
			terminate();
			break;
		}

		//std::cout << "global optimization" << std::endl; 
	}
}


//pause and resume
void global_optimization::request_pause(){

}

void global_optimization::is_paused(){

}

void global_optimization::resume(){

}


//terminate
void global_optimization::request_terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_terminate_is_requested = true;
}

bool global_optimization::is_terminated() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_is_terminated;
}

bool global_optimization::terminate_is_requested() const{
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	return m_terminate_is_requested;
}

void global_optimization::terminate(){
	std::lock_guard<std::mutex> lock(m_mtx_terminate);
	m_is_terminated = true;
}

} //namespace ezPano
