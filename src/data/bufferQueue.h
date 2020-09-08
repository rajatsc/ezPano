#ifndef _BUFFER_QUEUE_H
#define _BUFFER_QUEUE_H

/*
single producer, single consumer lock-free
bounded queue. 
*/

#include <iostream>
#include <atomic>
#include <vector>
#include <stdexcept>

namespace ezPano{

//template declaration
template<typename T>
class bufferQueue{
private:
	size_t m_capacity;
	std::vector<T> m_buffer;
	std::atomic<size_t> m_head;
	std::atomic<size_t> m_tail;
public:
	bufferQueue(const size_t capacity);

	// delete default constructor, non-copyable and non-movable
	bufferQueue() = delete;
	bufferQueue(const bufferQueue &) = delete;
	bufferQueue &operator=(const bufferQueue &) = delete;

	bool try_push(const T& item);
	void push(const T& item);
	bool front(T& item);
	void pop();
	
	size_t size() const;
	bool empty() const;
	size_t capacity() const;
};



template<typename T>
bufferQueue<T>::bufferQueue(const size_t capacity){
	m_capacity = capacity+1;
	m_head = 0;
	m_tail = 0;
	m_buffer.resize(capacity+1);
}



template<typename T>
void bufferQueue<T>::push(const T& item){
	size_t tail = m_tail.load(std::memory_order_seq_cst);
	size_t newTail = tail+1;
	
	if (newTail == m_capacity){
		newTail = 0;
	}

	while(newTail == m_head.load(std::memory_order_seq_cst))
	;

	m_buffer[m_tail]=item;
	m_tail.store(newTail, std::memory_order_seq_cst);
}


template<typename T>
bool bufferQueue<T>::try_push(const T& item){
	size_t tail = m_tail.load(std::memory_order_seq_cst);
	size_t newTail = tail+1;
	
	if (newTail == m_capacity){
		newTail = 0;
	}

	if (newTail == m_head.load(std::memory_order_seq_cst)){
		return false;
	}

	m_buffer[tail]=item;
	m_tail.store(newTail, std::memory_order_seq_cst);
	return true;
}


template<typename T>
void bufferQueue<T>::pop(){
	size_t head = m_head.load(std::memory_order_seq_cst);
	if (head == m_tail.load(std::memory_order_seq_cst)){
		throw std::runtime_error("trying to pop from an empty queue");
	}
	size_t newHead = (m_head + 1) % (m_capacity);
	m_head.store(newHead, std::memory_order_seq_cst);
	return;
}



template<typename T>
bool bufferQueue<T>::front(T& item){
	
	if (m_tail == m_head){
		return false;
	}
	item = m_buffer[m_head];
	return true;
}



template<typename T>
size_t bufferQueue<T>::size() const{
	return (m_tail+m_capacity-m_head)%(m_capacity);
}



template<typename T>
bool bufferQueue<T>::empty() const{
	return size() == 0;
}



template<typename T>
size_t bufferQueue<T>::capacity() const{
	return m_capacity-1;
}

}

#endif
