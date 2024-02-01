#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#ifndef UINT8_T_DEFINED
#define UINT8_T_DEFINED
#include <stdint.h> 
#endif 
#ifndef BOOT_DEFINED
#define BOOL_DEFINED
#include <stdbool.h> 
#endif 
#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
#include <stddef.h> 
#endif

/*
Byte Ring Buffer Implantation, buffer size must be a power of 2 
*/




typedef struct RingBuffer{
    volatile uint8_t * const buf;
    volatile size_t size;
    volatile uint8_t write;
    volatile uint8_t read;
}RingBuffer;

static RingBuffer rb_init( uint8_t * const buf, size_t size){
    //@Brief: Create Ring Buffer
    RingBuffer rb = {
        .buf = buf,
        .size = size,
        .write = 0,
        .read = 0
    };
    return rb;
}

static bool rb_empty(const RingBuffer *rb){
    //@Brief: Check if ring buffer is empty
    return rb->read == rb->write;
}

static bool rb_full(const RingBuffer *rb){
    //@Brief: Check if ring buffer is full
    //@Note: Writing to a full buffer will overwrite data
    uint8_t nextIdx = (rb->write + 1) & (rb->size - 1); // using bitwise AND for wrap-around
    return nextIdx == rb->read; 
}


static bool rb_put( RingBuffer *rb, const uint8_t data){
    //@Brief: Add one byte to ring buffer
    
    if(rb_full(rb)){return false;}
    rb->buf[rb->write] = data;
    rb->write = (rb->write +1) & (rb->size -1); // bitmask wrap around
    return true;
}

static bool rb_get(RingBuffer *rb, uint8_t *data){
    //@Brief: Remove one byte from ring buffer if available
    if(rb_empty(rb) == 1){return false;}
    *data = rb->buf[rb->read];
    rb->read = (rb->read + 1) & (rb->size -1); // bitmask wrap around
    return true;
}

static uint8_t rb_peek(const RingBuffer *rb){
    //@Brief: Get one byte from ring buffer without moving read index
    return rb->buf[rb->read];
}

#endif // RING_BUFFER_H