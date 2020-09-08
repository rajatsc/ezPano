#ifndef STITCHING_H
#define STITCHING_H

//local
#include "bufferQueue.h"

//standard
#include <mutex>

//opencv


namespace ezPano{


class stitching{
public:
	stitching();
	~stitching();
	void run();
	


	//-------------------------------------------
	//              pause and resume thread
	//-------------------------------------------
	void request_pause();
	bool is_paused() const;
	void resume();


	//---------------------------------------------
	//                terminate thread
	//---------------------------------------------
	
	void request_terminate();
	bool is_terminated() const;
	

private:
	//bufferQueue<frame> frame_bq;

	//---------------------------------------------
	//               pause and resume thread
	//--------------------------------------------
	mutable std::mutex m_mtx_pause;
	bool m_is_paused = false;
	bool m_pause_is_requested = false;

	//----------------------------------------------
	//                terminate thread
	//----------------------------------------------
	
	//! mutex to access the termination procedure
	mutable std::mutex m_mtx_terminate;
	
	//! flag which indicates termination is requested or not
	bool m_terminate_is_requested = false;

	//! flag which indicates whether the main loop is terminated
	bool m_is_terminated = true;

	
	void terminate();
	bool terminate_is_requested() const;

};

} //namespace ezPano

#endif
