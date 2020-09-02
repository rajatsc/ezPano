//standard
#include <chrono>
#include <iostream>
#include <string>
#include <csignal>
#include <thread>

//local
#include "system.h"
//#include "gui.h"


using namespace ezPano;

int main(int argc, char** argv){
	std::cout << "Hey there" << std::endl;
	
	//std::signal(SIGINT, signalHandler);
	ezPano::system s;
	s.startup();
	
	//viewer runs in the main thread
	ezPano::gui viewer(&s);

	std::thread worker(&system::start_feeding, &s);

	viewer.run();
	worker.join();

	/*
	auto finish = std::chrono::system_clock::now()+std::chrono::seconds{3};

	while(std::chrono::system_clock::now() < finish)
	{
		//do stuff
	}
	*/
	
	s.shutdown();

	return 0;

}
