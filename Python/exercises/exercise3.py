#!/usr/bin/env python3

'''Make a program to read a string from the input and print the index of uppercase letters in the string to the output.'''

# Get input from the user
user_input = input("Enter a string: ")

# index of uppercase letters
uppercaseletters = [index for index, char in enumerate(user_input) if char.isupper()]

# Print the result
if uppercaseletters:
    print("Indexes of uppercase letters:", uppercaseletters)
else:
    print("No uppercase letters found.")