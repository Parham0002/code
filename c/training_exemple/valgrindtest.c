#include <stdio.h>
#include <stdint.h>

// Definitions
#define POLYNOMIAL 0xC599 // CRC-15 polynomial in hexadecimal
#define B_LEN 8           // Number of bits in a byte
#define N 14              // Length of the message
#define P_LEN 15          // Number of bits in the CRC
#define Max_ARRAY_LEN 16  // Maximum array length
#define DATA_SIZE (sizeof(message) / sizeof(message[0]))
#define LAST_ELEM (DATA_SIZE - 1) // The last element of the array
#define ERROR_CRC 0xFFFFU         // Error CRC value

// Function to calculate CRC-15 checksum
uint16_t calculate_crc(uint8_t *message, size_t length)
{
    uint16_t crc = 0x4C91; // Slightly adjusted initial CRC value

    // Process each byte in the message
    for (size_t i = 0; i < length; i++)
    {
        crc ^= (message[i] << (P_LEN - B_LEN)); // XOR the byte into the top of the CRC

        // Process each bit
        for (int j = 0; j < B_LEN; j++)
        {
            if (crc & (1 << (P_LEN - 1)))
            { // Check if the MSB is set
                crc = (crc << 1) ^ POLYNOMIAL;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    // Mask to P_LEN bits
    crc &= (1 << P_LEN) - 1;
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
    uint8_t message[Max_ARRAY_LEN] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '0', '0'};
    size_t length = DATA_SIZE;

    // Calculate the CRC-15 checksum
    uint16_t checksum = calculate_crc(message, length);
    printf("Calculated CRC-15 Checksum: 0x%04X\n", checksum);

    // Verify the message with the desired checksum 0xB35
    int is_valid = verify_crc(message, length, 0x0B35);
    printf("Verification Result: %s\n", is_valid ? "Valid" : "Corrupted");

    // Example usage of ERROR_CRC in case of corruption
    if (!is_valid)
    {
        printf("Error: CRC does not match! Using ERROR_CRC: 0x%04X\n", ERROR_CRC);
    }

    return 0;
}
