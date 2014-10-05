/*
 * CircularBuffer.hpp
 *
 *  Created on: 18/10/2013
 *      Author: Wendell
 */

#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

#include <stdlib.h>
#include <pthread.h>

#include <QDebug>
#include <QByteArray>

namespace ayvu {

typedef struct circular_buffer {
	int length;
	int head;
	int tail;
	int size;
	char* buffer;
	pthread_mutex_t mutex;
} circular_buffer_t;

/**
 * Encapsulation of a circular buffer
 * read from head write to tail
 * size is constant available space
 * length is number of available unread bytes
 * mutex protects a complete frame read and write
 * buffer dynamically allocated
 */
circular_buffer_t* createCircularBuffer(int size);

void destroyCircularBuffer(circular_buffer_t* circular_buffer);

/**
 * Write to the tail index, increment it and do the modulo wrap-around
 */
void writeByteToCircularBuffer(circular_buffer_t* circular_buffer, char val);
/**
 * Read from the head index, increment it and do the modulo wrap-around
 */
char readByteFromCircularBuffer(circular_buffer_t* circular_buffer);

/**
 * Returns True/False - Either there is enough room or the call fails (false)<br>
 * Mutex protect the buffer<br>
 */
bool writeToCircularBuffer(circular_buffer_t* circular_buffer, char* buffer,
		int number_bytes);

/**
 * Returns True/False - Either there is data in the buffer to satisfy the request or it fails (false)<br>
 * Mutex protect the buffer<br>
 */
bool readFromCircularBuffer(circular_buffer_t* circular_buffer, char buffer[],
		int number_bytes);

}

#endif /* CIRCULARBUFFER_HPP_ */
