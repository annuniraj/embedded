#ifndef RING_H_
#define RING_H_
#define BUFFERSIZE	200

#include <stdint.h>
#include "stddef.h"


typedef uint32_t 	buff_size;

extern buff_size			WR_Samples[BUFFERSIZE],
					FCT_Samples[BUFFERSIZE],
					WL_Samples[BUFFERSIZE]; /// defined in state_Handler.c

typedef enum{
	NO_PTR = -3, /**< Returned if null pointer was given as parameter. */
	NO_DATA = -2, /**< Returned if there was no data to read in buffer. */
	NO_PLACE = -1, /**< Returned if there was no place to write data in buffer. */
	OK = 1 /**< Returned when write/read was succesfull/ */
} RingStatus_t;


typedef struct{
	size_t size; /**< Size of buffer given in elements. */
	size_t elementSize; /**< Size of one buffer element. */
	size_t sizeB; /**< Size of buffer given in bytes. */
	size_t elementsInBuffer; /**< Current count of elements in buffer. */
	uint32_t writePtr; /**< Buffer next write pointer. */
	uint32_t readPtr; /**< Buffer next read pointer. */
	uint32_t place; /**< Place available in buffer. */
	void* buffer; /**< Pointer to array holding ring buffer. */
} RingBuffer_t;

extern RingBuffer_t		WR_Ring,
					FCT_Ring,
					WL_Ring;//defined in state_Handler.c
/**
 * Function that returns size of whole ring buffer.
 *
 * @param buffer 	Pointer to buffer structure, which size has to be returned.
 * @retval 			Size of pointed ring buffer.
 */
uint32_t RingGetElementsCapacity (RingBuffer_t* buffer);

/**
 * @brief Function that returns available space in selected buffer.
 *
 * @param buffer Pointer to buffer structure, which size has to be returned.
 * @return uint32_t Available size in provided buffer.
 */
uint32_t RingGetSpace (RingBuffer_t* buffer);

/**
 * @brief Function that returns count of data available in buffer.
 *
 * @param buffer Pointer to buffer structure
 * @return uint32_t Data count in buffer.
 */
uint32_t RingGetDataCnt (RingBuffer_t* buffer);

/**
 * @brief Function to initialize selected ring buffer.
 *
 * @param buffer 	Pointer to buffer structure that has to be initialized.
 * @param arrayBuffer Pointer to array used by buffer
 * @param bufferSize Size of buffer given in elements
 * @param elementSize Size of one element
 * @return RingStatus_t
 */
RingStatus_t RingInit (RingBuffer_t* buffer, void* arrayBuffer, size_t bufferSize, size_t elementSize);

/**
 * @brief Function to initialize ring buffer with memory allocation
 *
 * @param buffer Pointer to buffer structure that has to be initialized.
 * @param bufferSize Size of buffer given in elements
 * @param elementSize Size of one element
 * @return RingStatus_t
 */
RingStatus_t RingInitAlloc (RingBuffer_t* buffer, size_t bufferSize, size_t elementSize);

/**
 * @brief Addes one byte to the end of buffer.
 *
 * @param buffer Pointer to buffer to write.
 * @param data Data to write.
 * @return RingStatus_t Status of write process.
 */
RingStatus_t RingWriteElement (RingBuffer_t* buffer, void* data);

/**
 * @brief Writes multiple bytes to buffer.
 *
 * @param buffer Buffer to write data.
 * @param data Data pointer to write.
 * @param len Length of data.
 * @return RingStatus_t Write status.
 */
RingStatus_t RingWriteElements (RingBuffer_t* buffer, void* data, size_t len);

/**
 * @brief Reads one byte from buffer.
 *
 * @param buffer Buffer to read.
 * @param data Pointer to save data.
 * @return RingStatus_t Read status.
 */
RingStatus_t RingReadElement (RingBuffer_t* buffer, void* data);

/**
 * @brief Reads multiple bytes from buffer.
 *
 * @param buffer Buffer to read data.
 * @param data Pointer to write data.
 * @param len Length of data to read.
 * @return RingStatus_t Read status.
 */
RingStatus_t RingReadElements (RingBuffer_t* buffer, void* data, size_t len);

/**
 * @brief Returns write pointer of buffer.
 *
 * @param buffer Buffer to get pointer.
 * @return uint32_t Write pointer.
 */
uint32_t RingGetHead (RingBuffer_t* buffer);

/**
 * @brief Returns read pointer of buffer.
 *
 * @param buffer Buffer to get pointer.
 * @return uint32_t Read pointer.
 */
uint32_t RingGetTail (RingBuffer_t* buffer);

/**
 * @brief Gets last element from buffer without taking it from buffer.
 *
 * @param buffer Buffer to read.
 * @return uint32_t Last byte in buffer.
 */
RingStatus_t RingGetLastElement(RingBuffer_t* buffer, void* element);

/**
 * @}
 *
 */
#endif /* RING_H_ */
