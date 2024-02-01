#include "../ringbuffer.h"

#include <stdio.h>
#include <assert.h>

#define RB_SIZE 64

void test_ring_buffer() {
    uint8_t rbBUF[RB_SIZE];
    uint8_t data;
    RingBuffer rb = rb_init(rbBUF, RB_SIZE);
    // Test 1: Check if the ring buffer is initially empty
    assert(rb_empty(&rb));

    // Test 2: Add data to the ring buffer 
    rb_put(&rb, 'X');
    assert(!rb_empty(&rb));
    assert(!rb_full(&rb));

    // Test 3: Peek at the data and check if it matches the value added
    assert(rb_peek(&rb) == 'X');

    // Test 4: Remove the data and check if the buffer is empty again
    rb_get(&rb, &data);
    assert(rb_empty(&rb));

    // Test 5: Add data until the buffer is full and check if it's full
    for (uint32_t i = 0; i < RB_SIZE; i++) {
        rb_put(&rb, i);
    }
    assert(rb_full(&rb));

    // Test 6: Remove data until the buffer is empty and check if it's empty
    for (uint32_t i = 0; i < RB_SIZE; i++) {
        rb_get(&rb, &data);
    }
    assert(rb_empty(&rb));

    // Test 7: Add data to the buffer and check if it wraps around correctly
    for (uint32_t i = 0; i < RB_SIZE * 2; i++) {
        assert(rb_put(&rb, i));
        assert(rb_get(&rb, &data));
    }
    assert(rb_empty(&rb));


    printf("All tests passed!\n");
}

int main() {
    test_ring_buffer();

    return 0;
}

