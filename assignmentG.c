        /**
         * @file assignmentG
         * @author Parham Rezaei (knightpslow@gmail.com)
         * @brief  Program to validate Swedish personal identity numbers (personnummer)
         * 
         * This program validates a Swedish personal identity number, known as "personnummer," 
         * using the Luhn algorithm. A valid personnummer follows the format "YYMMDD-NNNN," 
         * where YYMMDD represents the birth date, NNN is a unique identifier, and the 
         * last digit is a control digit. This control digit is calculated with the 
         * Luhn algorithm (modulus 10) to ensure data integrity.
         * 
         * The program accepts user input in the form of a personal identity number string. 
         * It then performs the following steps:
         * 
         * 1. **Format Verification**: The program checks that the input matches the 
         *    required "YYMMDD-NNNN" format, with the correct length, structure, and 
         *    valid numeric characters.
         * 2. **Control Digit Calculation**: Using the Luhn algorithm, the program 
         *    calculates a control digit based on the birth date and unique identifier.
         * 3. **Validation**: The calculated control digit is compared to the provided 
         *    control digit (last digit in the input) to determine if the personnummer 
         *    is valid or invalid.
         * 
         * The program output indicates if the provided number is valid or invalid, 
         * with helpful messages for incorrect input formats.
         * 
         * @version 0.1
         * @date 2024-11-07
         * 
         * @copyright Copyright (c) 2024
         * 
         */

        #include <stdio.h>
        #include <string.h>
        #include <ctype.h>

        #define PERSONNUM_LENGTH 11  // Expected length: "YYMMDD-NNNN" (excluding null terminator)
        #define SEPARATOR_POS 6      // Position of the separator '-'
        #define MODULO 10            // Modulus value for Luhn algorithm

        // Functions
        int valid_format(const char *personnum);
        int calculate_control_digit(const char *personnum);
        int valid_personnum(const char *personnum);


        int main() {
            char personnum[PERSONNUM_LENGTH + 2];  // +2 to account for null terminator and newline character
            char try_again;

            do{
            printf("Enter Swedish personal identity number (YYMMDD-NNNN): ");
            fgets(personnum, sizeof(personnum), stdin);

            // Remove any newline character from the input
            personnum[strcspn(personnum, "\n")] = '\0';

            // Error: check if the input lenght is correct
        if (valid_format(personnum)) {
                
                if (valid_personnum(personnum)) {
                    printf("The personal number %s is valid.\n", personnum);
                } else {
                    printf("The personal number %s is invalid.\n", personnum);
                }
            } else {
                printf("Error: Invalid format! Please enter in format YYMMDD-NNNN.\n");
            }

            // Promp the user to try again
            printf("do you want to check another personnummer ?(y/n)");
            try_again = getchar(); // Read the user input

            // Clear any remaining characters in the input buffer
            while (getchar() != '\n');

            
            }while (try_again== 'y' || try_again == 'Y');

        printf("Okey bye!\n");

            return 0;

        }

        // Check if the input format is valid
        int valid_format(const char *personnum) {
            // Check length; should be exactly PERSONNUM_LENGTH characters
            if (strlen(personnum) != PERSONNUM_LENGTH) {
                printf("Error: Length check failed it has to be 11.\n");  // Debug information
                return 0;
            }

            // Check for the '-' separator in the correct position
            if (personnum[SEPARATOR_POS] != '-') {
                printf("Error: Separator check failed.\n");  // Debug information
                return 0;
            }

            // Ensure all other characters are digits
            for (int i = 0; i < PERSONNUM_LENGTH; i++) {
                if (i == SEPARATOR_POS) continue;  // Skip the separator
                if (!isdigit(personnum[i])) {
                    printf("Error: Digit check failed at position %d.\n", i);  // Error information
                    return 0;
                }
            }

            return 1;  // Format is valid
        }

        // Calculate the control digit based on the Luhn algorithm
        int calculate_control_digit(const char *personnum) {
            int sum = 0;
            int multiplier = 2;  // Start multiplier at 2, then alternate

            // Loop over each digit before the separator and  the last four digits
            for (int i = 0; i < PERSONNUM_LENGTH - 1; i++) {
                if (i == SEPARATOR_POS) continue;  // Skip the separator '-'

                int digit = personnum[i] - '0';  // Convert char to int
                int product = digit * multiplier;

                // Sum the digits of the product (e.g., for a two-digit number, add both digits)
                if (product >= 10) {
                    sum += (product / 10) + (product % 10);
                } else {
                    sum += product;
                }

                // Alternate multiplier between 2 and 1
                
                if (multiplier == 2) {
                    multiplier = 1;   
                } else {
                    multiplier = 2;
                }
            }

            // Calculate control digit as 10 minus the last digit of the sum
            int control_digit = (MODULO - (sum % MODULO)) % MODULO;
            return control_digit;
        }

        // Validate the personal identity number by checking the control digit
        int valid_personnum(const char *personnum) {
            // Extract the last digit as the provided control digit
            int provided_control_digit = personnum[PERSONNUM_LENGTH - 1] - '0';

            // Calculate the correct control digit
            int calculated_control_digit = calculate_control_digit(personnum);

            // Compare provided and calculated control digits
            return provided_control_digit == calculated_control_digit;
        }