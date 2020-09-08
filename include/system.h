#ifndef SYSTEM_H
#define SYSTEM_H

//standard
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

//opencv
#include <opencv2/core/core.hpp>

//local
#include "feeder.h"
#include "tracking.h"
#include "stitching.h"
#include "global_optimization.h"
#include "bufferQueue.h"
#include "mosaicDatabase.h"

namespace ezPano{

class feeder;
class tracking;
class stitching;
class global_optimization;
class mosaic_db;

class system{
public:
	//!constructor
	system();

	//!destructor
	~system();
	
	//!start the system
	void startup();
	
	//!shutdown the system
	void shutdown();
	
	
	//----------------------------------
	//			reset the system
	//----------------------------------
	void request_reset();
	bool reset_is_requested() const;
	
	//start feeding
	void start_feeding();
	
	//pause the feeder	
	void pause_feeder();
	void resume_feeder();
	bool feeder_is_paused() const;
	
	//pause and resume  threads
	void pause_all_threads();
	void resume_all_threads();

private:
	
	//mosaic
	//mosaicDatabase* mosaic;

	//modules
	feeder* m_feeder=nullptr; //feeding module
	tracking* m_tracker=nullptr; //tracking module
	stitching* m_stitcher=nullptr; //stitching module
	global_optimization* m_global_optimizer=nullptr; //global optimization module

	//module threads
	std::thread* m_tracker_thread = nullptr;
	std::thread* m_stitcher_thread = nullptr;
	std::thread* m_global_optimizer_thread=nullptr;
	
	//! system running status flag
    std::atomic<bool> system_is_running{false};

};

} //namespace ezPano

#endif
