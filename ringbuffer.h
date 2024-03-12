#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Define the RingBuffer struct
typedef struct RingBuffer {
    void* buf;
    size_t size; // Total size of buffer in bytes
    size_t elementSize; // Size of each element in bytes
    size_t write;
    size_t read;
    size_t mask; // Mask for wrapping around the buffer
} RingBuffer;

RingBuffer rbInit(void* buf, const size_t size, const size_t elementSize) {
    RingBuffer rb;
    rb.buf = buf;
    rb.size = size;
    rb.elementSize = elementSize;
    rb.write = 0;
    rb.read = 0;
    rb.mask = size - 1; // Initialize the mask
    return rb;
}

// Function to check if the ring buffer is empty
bool rbEmpty(const RingBuffer *rb) {
    return rb->read == rb->write;
}

// Function to check if the ring buffer is full
bool rbFull(const RingBuffer *rb) {
    size_t nextIndex = (rb->write + 1) & rb->mask; // Calculate the next index
    return nextIndex == rb->read; // Buffer is full if next index is the read index
}

/// Core function for putting data into the buffer
bool rbPut(RingBuffer *rb, const void *data) {
    if (rbFull(rb)) {
        return false; // Buffer is full, cannot add more data
    }

    uint8_t *buffer = (uint8_t*)(rb->buf);

    // Calculate the index where the data should be stored
    size_t index = rb->write;

    // Copy data byte-by-byte into the buffer
    for (size_t i = 0; i < rb->elementSize; ++i) {
        buffer[(index * rb->elementSize) + i] = *((uint8_t*)data + i);
    }

    // Update the write index
    rb->write = (index + 1) & rb->mask;

    return true; // Data successfully added to the buffer
}

// Core function for getting data from the buffer
bool rbGet(RingBuffer *rb, void *data) {
    if (rbEmpty(rb)) {
        return false; // Buffer is empty, cannot retrieve data
    }

    uint8_t *buffer = (uint8_t*)(rb->buf);

    // Calculate the index from where data should be retrieved
    size_t index = rb->read;

    // Copy data byte-by-byte from the buffer
    for (size_t i = 0; i < rb->elementSize; ++i) {
        *((uint8_t*)data + i) = buffer[(index * rb->elementSize) + i];
    }

    // Update the read index
    rb->read = (index + 1) & rb->mask;

    return true; // Data successfully retrieved from the buffer
}

// Core function for peeking at the next data in the buffer
bool rbPeek(const RingBuffer *rb, void *data) {
    if (rbEmpty(rb)) {
        return false; // Buffer is empty, cannot peek data
    }

    uint8_t *buffer = (uint8_t*)(rb->buf);

    // Calculate the index of the next data to peek
    size_t index = rb->read;

    // Copy data byte-by-byte from the buffer
    for (size_t i = 0; i < rb->elementSize; ++i) {
        *((uint8_t*)data + i) = buffer[(index * rb->elementSize) + i];
    }

    return true; // Data peeked successfully
}

void rbClear(RingBuffer *rb) {
    rb->write = rb->read = 0;
}

void rbFill(RingBuffer *rb, void *value) {
    if (rb == NULL || value == NULL) {
        return; // Check for NULL pointers
    }

    size_t element_size = rb->elementSize;
    size_t buffer_size = rb->elementSize;
    size_t total_size = element_size * buffer_size;

    // Cast the value pointer to the appropriate type
    uint8_t *fill_value_ptr = (uint8_t *)value;

    // Iterate through the buffer and fill each element with the value
    for (size_t i = 0; i < total_size; i += element_size) {
        for (size_t j = 0; j < element_size; j++) {
            *((uint8_t *)rb->buf + i + j) = fill_value_ptr[j];
        }
    }

    rb->write = rb->read = 0; // Reset head and tail pointers
}


#endif // RING_BUFFER_H
