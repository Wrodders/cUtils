#include <stdio.h>
#include <assert.h>
#include "../ringbuffer.h"

#define BUF_SIZE 1024 // Adjusted to be a power of 2
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main() {

    // Create buffer for uint8_t
    uint8_t uint8_buffer[BUF_SIZE] = {0}; // Initialize buffer to 0
    RingBuffer rbUint8 = rbInit(uint8_buffer, ARRAY_SIZE(uint8_buffer), sizeof(uint8_t));

    // Test filling and emptying uint8_t buffer
    uint8_t data_uint8 = 1;
    for (int i = 0; i < BUF_SIZE; i++) {
        rbPut(&rbUint8, &data_uint8); // Fill buffer
        data_uint8++;
    }
    assert(rbFull(&rbUint8)); // Assert buffer is full after population

    // Test emptying uint8_t buffer
    for (int i = 0; i < BUF_SIZE; i++) {
        uint8_t value;
        if(rbGet(&rbUint8, &value)== false){break;} // Retrieve data from buffer
        assert(value == (uint8_t)(i + 1)); // Assert the correctness of received data
    }
    assert(rbEmpty(&rbUint8)); // Assert buffer is empty after retrieval

    // Test peeking into uint8_t buffer
    data_uint8 = 10;
    for (int i = 0; i < BUF_SIZE; i++) {
        rbPut(&rbUint8, &data_uint8); // Fill buffer
        data_uint8++;
    }
    uint8_t peek_value;
    assert(rbPeek(&rbUint8, &peek_value)); // Peek into buffer
    assert(peek_value == 10); // Assert the correctness of peeked data

    // Test edge case: buffer overflow
    uint8_t overflow_data = 100;
    assert(!rbPut(&rbUint8, &overflow_data)); // Try adding data when buffer is full, should fail

    // clear buffer 
    rbClear(&rbUint8);
    // Test edge case: buffer underflow
    uint8_t underflow_value;
    assert(!rbGet(&rbUint8, &underflow_value)); // Try retrieving data when buffer is empty, should fail

    // Create buffer for floats
    float float_buffer[BUF_SIZE] = {0}; // Initialize buffer to 0
    RingBuffer rbFloat = rbInit(float_buffer, ARRAY_SIZE(float_buffer), sizeof(float));

    // Test adding and retrieving float data without checking buffer fullness
    float data_float = 1.0f; // Constant float value
    for (int i = 0; i < BUF_SIZE; i++) {
        rbPut(&rbFloat, &data_float); // Fill buffer with constant float value
    }
    assert(rbFull(&rbFloat)); // Assert buffer is full after population

    // Test emptying float buffer
    float expected_value = 1.0f;
    for (int i = 0; i < BUF_SIZE; i++) {
        float value;
        if(rbGet(&rbFloat, &value) == false){break;}// Retrieve data from buffer
        assert(value == expected_value); // Assert the correctness of received data
    }


    // Test edge case: buffer underflow
    float underflow_value_float;
    assert(!rbGet(&rbFloat, &underflow_value_float)); // Try retrieving data when buffer is empty, should fail

    // Create buffer for ints
    int int_buffer[BUF_SIZE] = {0}; // Initialize buffer to 0
    RingBuffer rbInt = rbInit(int_buffer, ARRAY_SIZE(int_buffer), sizeof(int));

    // Test adding and retrieving int data without checking buffer fullness
    int data_int = 1;
    for (int i = 0; i < BUF_SIZE; i++) {
        rbPut(&rbInt, &data_int); // Fill buffer
        data_int++;
    }
    assert(rbFull(&rbInt)); // Assert buffer is full after population

    // Test emptying int buffer
    for (int i = 0; i < BUF_SIZE; i++) {
        int value;
        if(rbGet(&rbInt, &value)== false){break;} // Retrieve data from buffer
        assert(value == i + 1); // Assert the correctness of received data
    }

    // Test edge case: buffer underflow
    int underflow_value_int;
    assert(!rbGet(&rbInt, &underflow_value_int)); // Try retrieving data when buffer is empty, should fail
    printf("All Tests Passed!\n");

    return 0;
}
