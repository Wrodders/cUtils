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




#define RING_BUFFER_SIZE 10

typedef struct RingBuffer{
    volatile uint8_t buf[RING_BUFFER_SIZE];
    volatile uint8_t size;
    volatile uint8_t head;
    volatile uint8_t tail;
}RingBuffer;

static void rb_init(RingBuffer *rb,  uint16_t size){
    //@Breif: Create Ring Buffer
    rb->size = size;
    for(int i = 0; i < RING_BUFFER_SIZE; i++){
        rb->buf[i] = 0;
    }
}

static bool rb_empty(const RingBuffer *rb){
    //@Breif: Check if ring buffer is empty
    return rb->tail == rb->head;
}

static bool rb_full(const RingBuffer *rb){
    //@Breif: Check if ring buffer is full
    uint8_t nextIdx = rb->head + 1;
    if(nextIdx == rb->size){
        nextIdx = 0;
    }
    return nextIdx == rb->tail; 
}


static void rb_put( RingBuffer *rb, const uint8_t data){
    //@Breif: Add one byte to ring buffer
    if(rb_full(rb) == 1) {return;}
    rb->buf[rb->head++] = data;
    rb->head = rb->head == rb->size ? 0 : rb->head; // reset head if end
    return;
}

static uint8_t rb_get(RingBuffer *rb){
    //@Breif: Remove one byte from ring buffer
    if(rb_empty(rb) == 1){return 0;}
    const uint8_t data = rb->buf[rb->tail++];
    rb->tail = rb->tail == rb->size ? 0 : rb->tail; // reset tail if end
    return data;
}

static uint8_t rb_peek(const RingBuffer *rb){
    //@Breif: Get one byte from ring buffer without removing it
    return rb->buf[rb->tail];
}



#endif // RING_BUFFER_H