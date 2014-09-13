/*
 * CircularBuffer.cpp
 *
 *  Created on: 18/10/2013
 *      Author: Wendell
 */

#include "CircularBuffer.h"

namespace ayvu {

/**
 * Encapsulation of a circular buffer
 * read from head write to tail
 * size is constant available space
 * length is number of available unread bytes
 * mutex protects a complete frame read and write
 * buffer dynamically allocated
 */
circular_buffer_t* createCircularBuffer(int size) {
	circular_buffer_t* circular_buffer = (circular_buffer_t*) malloc(
			sizeof(circular_buffer_t));
	memset(circular_buffer, 0, sizeof(circular_buffer_t));
	circular_buffer->buffer = (char*) malloc(size);
	circular_buffer->size = size;
	pthread_mutex_init(&circular_buffer->mutex, NULL);
	return circular_buffer;
}

void destroyCircularBuffer(circular_buffer_t* circular_buffer) {
	pthread_mutex_destroy(&circular_buffer->mutex);
	free(circular_buffer->buffer);
	free(circular_buffer);
}

/**
 * Write to the tail index, increment it and do the modulo wrap-around
 */
void writeByteToCircularBuffer(circular_buffer_t* circular_buffer, char val) {
	++circular_buffer->length;
	circular_buffer->buffer[circular_buffer->tail] = val;
	++circular_buffer->tail;
	// Modulo arithmetic
	circular_buffer->tail %= circular_buffer->size;
}

/**
 * Read from the head index, increment it and do the modulo wrap-around
 */
char readByteFromCircularBuffer(circular_buffer_t* circular_buffer) {
	--circular_buffer->length;
	char val = circular_buffer->buffer[circular_buffer->head];
	++circular_buffer->head;
	// Modulo arithmetic
	circular_buffer->head %= circular_buffer->size;
	return val;
}

/**
 * Returns True/False - Either there is enough room or the call fails (false)<br>
 * Mutex protect the buffer<br>
 */
bool writeToCircularBuffer(circular_buffer_t* circular_buffer, char* buffer,
		int number_bytes) {
	// Check there's room
	// Not inside the mutex as it's read only
	// Mutex protect a number_bytes write to the circular buffer

	if (circular_buffer->length + number_bytes > circular_buffer->size) {
		qDebug() << "writeToCircularBuffer fail...";
		qDebug() << "SIZE: " << circular_buffer->size;
		qDebug() << "Lenght: " << circular_buffer->length;
		qDebug() << "+Bytes: " << number_bytes;
		qDebug() << "Lenght + Bytes: "
				<< circular_buffer->length + number_bytes;
		return false;
	}
	pthread_mutex_lock(&circular_buffer->mutex);
	for (int i = 0; i < number_bytes; ++i) {
		writeByteToCircularBuffer(circular_buffer, buffer[i]);
	}
	pthread_mutex_unlock(&circular_buffer->mutex);
	return true;
}

/**
 * Returns True/False - Either there is data in the buffer to satisfy the request or it fails (false)<br>
 * Mutex protect the buffer<br>
 */
bool readFromCircularBuffer(circular_buffer_t* circular_buffer, char buffer[],
		int number_bytes) {
	// Check there's sufficient data
	// Not inside the mutex as it's read only
	// Mutex protect a number_bytes read from the circular buffer

	if (circular_buffer->length < number_bytes) {
		return false;
	}
	int i;
	pthread_mutex_lock(&circular_buffer->mutex);
	for (i = 0; i < number_bytes; ++i) {
		buffer[i] = readByteFromCircularBuffer(circular_buffer);
	}
	pthread_mutex_unlock(&circular_buffer->mutex);
	return true;
}
}
