#!/usr/bin/env python3
'''string = "hello world"
print(string)  # Output: hello world

word = "Hello"
print(word[2])  # Output: l

# Slicing [start:end:step]
print(word[1:3])  # Output: el
print(word[-1])  # Output: o
print(word[2:-1])  # Output: ll
print(word[::-1])  # Output: olleH (Reverse the string)

# Correct way to modify a string
word = word.replace('e', 'E')
print(word)  # Output: HEllo

name = input("What is your name? ")
age = int(input("How old are you? "))
print("{} is {} years old.".format(name, age))


import sys
print (sys.argv)

number = input("Enter a number between 1 and 10: ")
if number.isnumeric():  # Check if the input is a number
    number = int(number)
    if number < 1:
        print("Number is too small!")
    elif number > 10:
        print("Number is too big!")
    else:
        print("You chose the number {}".format(number))
else:
    print("The entered data was not a number!")
    
    # First approach (Using for loop)
for n in range(2, 10):  # Check numbers from 2 to 9
    for x in range(2, n):  # Check divisibility from 2 to n-1
        if n % x == 0:  # If n is divisible by x, it's not prime
            break
    else:  # If no divisor was found, the number is prime
        print(n, 'is prime')

# Second approach (Using while loop)
for n in range(2, 10):  # Check numbers from 2 to 9
    x = 2
    while x < n:  # Check divisibility from 2 to n-1
        if n % x == 0:  # If n is divisible by x, it's not prime
            break
        x += 1  # Increment x for the next divisor check
    else:  # If no divisor was found, the number is prime
        print(n, 'is prime')'''
        
'''for V in range (0, 10, 2):
    
 print(V)'''
        
string = "hello"

name = string

name = name.replace("h", "K")

name = name.index("o")

'''for i, V in enumerate(string):
    
 print(i, V)'''
 


print(string, name)
        


