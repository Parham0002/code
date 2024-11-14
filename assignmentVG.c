#include <stdio.h>
#include <stdint.h>

// Definitions
#define POLYNOMIAL 0xC599  // CRC-15 polynomial in hexadecimal
#define B_LEN 8            // Number of bits in a byte
#define N 14               // Length of the message
#define P_LEN 15           // Number of bits in the CRC
#define INITIAL_CRC 0x1D0F // Another initial CRC value to try
#define FINAL_XOR 0xFFFF   // A different final XOR value to test

// Function to calculate CRC-15 checksum
uint16_t calculate_crc(uint8_t *message, size_t length)
{
    uint16_t crc = INITIAL_CRC; // Use the adjusted initial CRC value

    // Process each byte in the message
    for (size_t i = 0; i < length; i++)
    {
        crc ^= (message[i] << 7); // XOR the byte into the top of the CRC

        // Process each bit
        for (int j = 0; j < B_LEN; j++)
        {
            if (crc & (1 << (P_LEN - 1)))
            {
                crc = (crc << 1) ^ POLYNOMIAL;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    // Mask to 15 bits and apply final XOR value
    crc &= (1 << P_LEN) - 1;
    crc ^= FINAL_XOR;
    return crc;
}

// Function to verify the message with its CRC checksum
int verify_crc(uint8_t *message, size_t length, uint16_t checksum)
{
    uint16_t calculated_crc = calculate_crc(message, length);
    return (calculated_crc == checksum);
}

int main()
{
    // Hardcoded message "Hello World!00"
    uint8_t message[N] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '0', '0'};
    size_t length = sizeof(message) / sizeof(message[0]);

    // Calculate the CRC-15 checksum
    uint16_t checksum = calculate_crc(message, length);
    printf("Calculated CRC-15 Checksum: 0x%04X\n", checksum);

    // Verify the message with the calculated checksum
    int is_valid = verify_crc(message, length, checksum);
    printf("Verification Result: %s\n", is_valid ? "Valid" : "Corrupted");

    return 0;
}
