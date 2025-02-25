#!/usr/bin/env python3

# Function to calculate the factorial of a number
def factorial(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n - 1)

# Input: Read an integer from the user
try:
    num = int(input("Enter a number greater than 0: "))
    if num <= 0:
        print("Please enter a number greater than 0.")
    else:
        # Calculate the factorial
        result = factorial(num)
        print(f"The factorial of {num} is: {result}")
except ValueError:
    print("Please enter a valid integer.")
