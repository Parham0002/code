/**
 * @file assignmentVG
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief  Program to calculate CRC-15
 *
 * This program calculates the CRC-15 (Cyclic Redundancy Check) for a given
 * input message. The CRC-15 is a checksum algorithm used to detect errors
 * in data transmission.
 * The program takes a message as input and calculates the CRC-15 checksum
 * using the specified polynomial.
 * The result is printed to the console.
 *
 * @version 0.1
 * @date 2024-11-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdio.h>
#include <stdint.h>

#define POLYNOMIAL 0xC599                          // CRC-15 polynomial
#define B_LEN 8                                    // Bit length of each byte
#define N 14                                       // Maximum number of bytes in the message
#define P_LEN 15                                   // Length of the polynomial
#define Max_ARRAY_LEN 16                           // Maximum array length
#define DATA_SIZE (sizeof(data) / sizeof(data[0])) // Data size calculation
#define LAST_ELEM (data_len - 1)                   // Last element index
#define BEF_LAST_ELEM (data_len - 2)               // Before last element index
#define ERROR_CRC 0xFFFFU                          // Error CRC value

uint16_t calculate_crc(uint8_t *data, uint8_t data_len);

int verify_crc(uint8_t *data, uint8_t data_len, uint16_t crc);

int main()
{
    // Example message "Hello World!" as an array of uint8_t
    uint8_t data[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '0', '0'};
    uint8_t data_len = DATA_SIZE;

    // Calculate CRC
    uint16_t crc = calculate_crc(data, data_len);
    printf("CRC-15 Checksum: 0x%04X\n", crc);

    // Verify the data
    if (verify_crc(data, data_len, crc))
    {
        printf("Data is valid.\n");
    }
    else
    {
        printf("Data is corrupted.\n");
    }

    return 0;
}

uint16_t calculate_crc(uint8_t *data, uint8_t data_len)
{
    uint16_t crc = 0; // Initialize CRC

    // Process each byte in the data
    for (uint8_t i = 0; i < data_len; i++)
    {
        uint8_t current_byte = data[i];

        // Process each bit from LSB to MSB
        for (uint8_t bit = 0; bit < B_LEN; bit++)
        {
            uint8_t bit_value = (current_byte >> bit) & 1;
            if ((crc & 0x4000) != 0)
            { // If the 15th bit is set
                crc = ((crc << 1) | bit_value) ^ POLYNOMIAL;
            }
            else
            {
                crc = (crc << 1) | bit_value;
            }
            crc &= 0x7FFF; // Keep CRC within 15 bits
        }
    }

    // Append 15 zero bits to calculate the remainder
    for (uint8_t bit = 0; bit < P_LEN; bit++)
    {
        if ((crc & 0x4000) != 0)
        { // If the 15th bit is set
            crc = (crc << 1) ^ POLYNOMIAL;
        }
        else
        {
            crc <<= 1;
        }
        crc &= 0x7FFF; // Keep CRC within 15 bits
    }

    return crc;
}
int verify_crc(uint8_t *data, uint8_t data_len, uint16_t crc)
{
    uint16_t calculated_crc = calculate_crc(data, data_len);
    return (calculated_crc == crc) ? 1 : 0;
}