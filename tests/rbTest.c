#include "../ringbuffer.h"

#include <stdio.h>
#include <assert.h>

void test_ring_buffer() {
    RingBuffer rb;
    rb_init(&rb, RING_BUFFER_SIZE);

    // Test 1: Check if the ring buffer is initially empty
    assert(rb_empty(&rb));

    // Test 2: Add data to the ring buffer and check if it is not empty
    rb_put(&rb, 42);
    assert(!rb_empty(&rb));

    // Test 3: Peek at the data and check if it matches the value added
    assert(rb_peek(&rb) == 42);

    // Test 4: Remove the data and check if the buffer is empty again
    rb_get(&rb);
    assert(rb_empty(&rb));

    // Test 5: Add data until the buffer is full and check if it's full
    for (uint8_t i = 0; i < RING_BUFFER_SIZE; i++) {
        rb_put(&rb, i);
    }
    assert(rb_full(&rb));

    // Test 6: Remove data until the buffer is empty and check if it's empty
    for (uint8_t i = 0; i < RING_BUFFER_SIZE; i++) {
        rb_get(&rb);
    }
    assert(rb_empty(&rb));

    // Test 7: Add data to the buffer and check if it wraps around correctly
    for (uint8_t i = 0; i < RING_BUFFER_SIZE * 2; i++) {
        rb_put(&rb, i);
    }
    assert(rb_full(&rb));

    // Test 8: Check if writing to a full buffer discards the message
   // Attempt to write more data to the full buffer
    rb_put(&rb, 42);  // This should be discarded

    // Verify that the buffer is still full and the head position did not change
    assert(rb_full(&rb));
    assert(rb_peek(&rb) != 42);  // Ensure that the value written after the buffer is full is not present


    printf("All tests passed!\n");
}

int main() {
    test_ring_buffer();

    return 0;
}

