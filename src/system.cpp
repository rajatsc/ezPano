//standard
#include <iostream>
#include <chrono>

//local
#include "system.h"

namespace ezPano{

system::system()
{
	std::cout << std::endl;
	std::cout << R"( _______   ________  ________  ________  ________   ________     )" << std::endl;
	std::cout << R"(|\  ___ \ |\_____  \|\   __  \|\   __  \|\   ___  \|\   __  \    )" << std::endl;
	std::cout << R"(\ \   __/| \|___/  /\ \  \|\  \ \  \|\  \ \  \\ \  \ \  \|\  \   )" << std::endl;
	std::cout << R"( \ \  \_|/__   /  / /\ \   ____\ \   __  \ \  \\ \  \ \  \\\  \  )" << std::endl;
	std::cout << R"(  \ \  \_|\ \ /  /_/__\ \  \___|\ \  \ \  \ \  \\ \  \ \  \\\  \ )" << std::endl;
	std::cout << R"(   \ \_______\\________\ \__\    \ \__\ \__\ \__\\ \__\ \_______\)" << std::endl;
	std::cout << R"(    \|_______|\|_______|\|__|     \|__|\|__|\|__| \|__|\|_______|)" << std::endl;
	std::cout << std::endl;

try{
	
	m_tracker = new tracking();
	m_stitcher = new stitching();
	m_global_optimizer = new global_optimization();
}

catch(std::exception& ex){
	
	/*
	note not sure if feeder and tracking will be deleted if stitchingthrows an error

	*/
	std::cout << "Exception happened" << std::endl;
}


}


system::~system(){
	
	delete m_feeder;
	m_feeder = nullptr;

	
	m_tracker_thread = nullptr;
	delete m_tracker;
	m_tracker = nullptr;

	m_stitcher_thread = nullptr;
	delete m_stitcher;
	m_stitcher = nullptr;

	m_global_optimizer_thread = nullptr;
	delete m_global_optimizer;
	m_global_optimizer = nullptr;

	std::cout << "destroying system" << std::endl;


}


void system::startup()
{

std::cout << "starting up stitching system" << std::endl;
system_is_running = true;


//initialize and run threads
m_tracker_thread = new std::thread(&ezPano::tracking::run, m_tracker);
m_stitcher_thread = new std::thread(&ezPano::stitching::run, m_stitcher);
m_global_optimizer_thread = new std::thread(&ezPano::global_optimization::run, m_global_optimizer);

}


void system::shutdown()
{
	//terminate the other threads
	m_tracker->request_terminate();
	m_stitcher->request_terminate();
	m_global_optimizer->request_terminate();

	//wait till all the threads have terminated
	while(!m_tracker->is_terminated() || !m_stitcher->is_terminated() || !m_global_optimizer->is_terminated()){
		std::this_thread::sleep_for(std::chrono::microseconds(5000));
	}

	

	//wait till the threads stop	
	m_tracker_thread->join();
	m_stitcher_thread->join();
	m_global_optimizer_thread->join();
	
	system_is_running = false;
	
	std::cout << "system succesfully shut down" << std::endl;
}


//pause feeder



void system::start_feeding(){
	std::cout << "feeding-------------------" << "\n";
	m_feeder->feed();
}


void system::pause_all_threads(){
	//pause the tracking module
	if (m_tracker && !m_tracker->is_terminated()){
		m_tracker->request_pause();

		//wait for the tracking thread has finished pausing
		
	}

	//pause the stitching module
	if (m_stitcher && !m_stitcher->is_terminated()){
		m_stitcher->request_pause();

		//wait for stitching thread has finished pausing
	}

	//pause the global optimization module
	if (m_global_optimizer && !m_global_optimier->is_terminated()){
		m_global_optimizer->request_pause();

		//wait for global optimization has finished pausing
	}

}

void system::resume_all_threads(){
	//resume tracking module
	if (m_tracker){
		m_tracker->resume();
	}

	//resume stitching module
	if (m_stitcher){
		m_stitcher->resume();
	}

	//resume the global optimiation module
	if (m_global_optimizer){
		m_global_optimizer->resume();
	}
}


} //namespace ezPano

