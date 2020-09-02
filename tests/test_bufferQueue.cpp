#include "tests/base.h"
#include "bufferQueue.h"

//standard
#include <thread>
#include <atomic>
#include <cassert>
#include <chrono>
#include <vector>

//opencv
#include <opencv2/core/core.hpp>

void test_basics(){
	EZPANO_TEST_BEGIN("test basics");
	
	ezPano::bufferQueue<int> bq(10);
	
	int a = bq.capacity();
	int b = bq.size();
	
	EZPANO_ASSERT_EQUAL(a, 10);
	EZPANO_ASSERT_EQUAL(b, 0);
	EZPANO_EXPECT_EXCEPTION(bq.pop(), std::runtime_error);

	//push elements
	for (int i=0; i < 10; i++){
		EZPANO_ASSERT_THROW(bq.try_push(i) == true);
		EZPANO_ASSERT_EQUAL(bq.size(), i+1);
	}

	EZPANO_ASSERT_THROW(bq.try_push(10) == false);
		
	//pop elements
	int out;
	EZPANO_ASSERT_THROW(bq.front(out) == true);
	EZPANO_ASSERT_EQUAL(out, 0);
	bq.pop();
	
	for (int i=1; i < 10; i++){
		EZPANO_ASSERT_THROW(bq.front(out) == true);
		bq.pop();
		EZPANO_ASSERT_EQUAL(out, i);
		EZPANO_ASSERT_EQUAL(bq.size(), 9-i);
	}
	

	EZPANO_TEST_END();
}



void test_cv(){	
	ezPano::bufferQueue<cv::Mat> bqmat(10);

	EZPANO_ASSERT_EQUAL(bqmat.capacity(), 10);
	EZPANO_ASSERT_EQUAL(bqmat.size(), 0);
}


void test_multithreaded(){
	int iter = 100;
	ezPano::bufferQueue<int> bq(iter/10);
	std::atomic<bool> flag(false);
	
	std::thread producer([&]{
		while(!flag)
			;
		for (int i=0; i < iter; i++){
			bq.push(i);
		}
	});

	int sum = 0;
	std::vector<int> output;
	int x;
	flag = true;
	for (int i=0; i < iter; i++){
		while(!bq.front(x))
			;
		sum = sum + x;
		output.push_back(x);
		bq.pop();
	}
	
	EZPANO_ASSERT_THROW(bq.front(x) == false);
	EZPANO_ASSERT_EQUAL(sum, iter*(iter-1)/2);
	EZPANO_ASSERT_EQUAL(output.size(), iter);

	for (int i=0; i < iter; i++){
		EZPANO_ASSERT_EQUAL(output[i], i);
	}

	producer.join();

}

int main(){		
	test_basics();
	//test_cv();
	test_multithreaded();
	
	return 0;
}
