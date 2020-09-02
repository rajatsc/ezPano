#ifndef FEEDER_H
#define FEEDER_H

#include <mutex>

#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>

#include "tracking.h"

namespace ezPano{

//image pre-processor
class imageProcessor
{
public:
    imageProcessor()
		:m_NextProcessor(nullptr){}

	virtual ~imageProcessor(){}

    void process(cv::Mat& im) {
        processImplementation(im);
        if (m_NextProcessor) 
            m_NextProcessor->process(im);
    }

    void setNextProcessor(imageProcessor *p) {
        m_NextProcessor = p;
    }

protected:
    virtual void processImplementation(cv::Mat& im) = 0;

private:
    imageProcessor* m_NextProcessor;
};



//identity image pre-processor
class identity: public imageProcessor
{
private:
	void processImplementation(cv::Mat& im);
};


//scale 



//filter




//feeder
class feeder
{
public:
	feeder(int _deviceID, int _frame_skip);
	~feeder();
	
	virtual void feed();

	//pause
	void request_pause();
	bool is_paused() const;

	//terminate
	void request_terminate();
	bool is_terminated() const;

	//resume
	void resume();

private:
	imageProcessor* processor=nullptr;
	
	bool is_finished = false;
	cv::Mat im;
	cv::VideoCapture cap;
	int deviceID;
	int frame_skip;
	
	tracking* m_tracker;
	
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
