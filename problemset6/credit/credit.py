from cs50 import get_int
from sys import exit
import math


# Dictionary of cards
cards = {
    "34": "AMEX",
    "37": "AMEX",
    "51": "MASTERCARD",
    "52": "MASTERCARD",
    "53": "MASTERCARD",
    "54": "MASTERCARD",
    "55": "MASTERCARD"
}


def main():
    # Get Number
    n = str(get_int("Number: "))

    # Check valid length
    if len(n) > 16 or len(n) < 13 or len(n) == 14:
        print("INVALID")
        exit(1)

    # Run Luhn test and print card type if successfull
    if pass_luhn(n):
        printcard(n)
        exit(0)
    else:
        print("INVALID")
        exit(1)


# End of main() function


# Check if number passes Luhn test
def pass_luhn(number):
    checksum = 0
    for i in range(len(number)):
        cd = int(number[len(number) - i - 1])
        if i % 2 == 0:
            checksum += cd
        else:
            checksum += (2 * cd) % 10 + math.floor(2 * cd / 10)
    if (checksum % 10 == 0):
        return True
    else:
        return False


# Print card type depending on first digits
def printcard(n):
    if n[:2] in cards:
        print(cards[n[:2]])
        exit(0)
    elif n[0] == "4":
        print("VISA")
        exit(0)
    else:
        print("INVALID")
        exit(1)


# Run main() function
main()