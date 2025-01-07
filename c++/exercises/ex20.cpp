#include <iostream>
#include <cassert>
#include <vector>
#include <cstdint>
#include <cmath>

class Buffer
{
private:
    uint8_t *buffer; // Pointer to the buffer array
    size_t size;     // Size of the buffer in bytes

public:
    // Constructor: Create a buffer with the specified size
    Buffer(size_t size)
    {
        this->size = size;
        buffer = new uint8_t[size];
        clear(); // Initialize buffer to 0
    }

    // Destructor: Free the buffer memory
    ~Buffer()
    {
        delete[] buffer;
    }

    // Clear: Reset all bytes in the buffer to 0
    void clear()
    {
        for (size_t i = 0; i < size; ++i)
        {
            buffer[i] = 0;
        }
    }

    // Insert data into the buffer
    void insert(int value, size_t bitLength, size_t startBit)
    {
        assert(bitLength > 0 && bitLength <= 32); // Support up to 32-bit integers
        size_t bytePos = startBit / 8;            // Starting byte position
        size_t bitOffset = startBit % 8;          // Bit offset within the starting byte
        size_t bitsToWrite = bitLength;

        while (bitsToWrite > 0)
        {
            size_t availableBits = 8 - bitOffset; // Bits available in the current byte
            size_t writeBits = std::min(bitsToWrite, availableBits);

            // Mask the bits to write
            uint8_t mask = (1 << writeBits) - 1;
            uint8_t valueToWrite = (value & mask) << bitOffset;

            // Insert into the buffer
            buffer[bytePos] &= ~(mask << bitOffset); // Clear target bits
            buffer[bytePos] |= valueToWrite;         // Write the new bits

            // Move to the next part
            value >>= writeBits; // Remove written bits from value
            bitsToWrite -= writeBits;
            bitOffset = 0;
            ++bytePos;
        }
    }

    // Extract data from the buffer
    int extract(size_t bitLength, size_t startBit) const
    {
        assert(bitLength > 0 && bitLength <= 32); // Support up to 32-bit integers
        size_t bytePos = startBit / 8;            // Starting byte position
        size_t bitOffset = startBit % 8;          // Bit offset within the starting byte
        size_t bitsToRead = bitLength;

        int result = 0;
        size_t resultShift = 0;

        while (bitsToRead > 0)
        {
            size_t availableBits = 8 - bitOffset; // Bits available in the current byte
            size_t readBits = std::min(bitsToRead, availableBits);

            // Extract the bits
            uint8_t mask = (1 << readBits) - 1;
            uint8_t extractedBits = (buffer[bytePos] >> bitOffset) & mask;

            // Add to result
            result |= (extractedBits << resultShift);

            // Move to the next part
            bitsToRead -= readBits;
            resultShift += readBits;
            bitOffset = 0;
            ++bytePos;
        }

        return result;
    }

    // Insert float into the buffer
    void insertFloat(float value, size_t bitLength, size_t startBit, float precision = 0.01f)
    {
        int scaledValue = static_cast<int>(round(value / precision));
        insert(scaledValue, bitLength, startBit);
    }

    // Extract float from the buffer
    float extractFloat(size_t bitLength, size_t startBit, float precision = 0.01f) const
    {
        int scaledValue = extract(bitLength, startBit);
        return scaledValue * precision;
    }

    // Display the buffer (for debugging purposes)
    void display() const
    {
        for (size_t i = 0; i < size; ++i)
        {
            printf("%02X ", buffer[i]);
        }
        printf("\n");
    }
};

// Test the Buffer class
void testBuffer()
{
    Buffer buffer(10); // Create a buffer of 10 bytes

    // Test integer insertion and extraction
    buffer.insert(42, 7, 4); // Insert 42 (7 bits) starting at bit 4
    assert(buffer.extract(7, 4) == 42);

    // Test float insertion and extraction
    buffer.insertFloat(3.14f, 16, 10); // Insert 3.14 as a 16-bit value at bit 10
    assert(abs(buffer.extractFloat(16, 10) - 3.14f) < 0.01f);

    // Test clearing the buffer
    buffer.clear();
    assert(buffer.extract(7, 4) == 0);

    // Display results for debugging
    buffer.display();

    std::cout << "All tests passed!" << std::endl;
}
int main()
{
    testBuffer();
    return 0;
}