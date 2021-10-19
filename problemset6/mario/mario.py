from cs50 import get_int

# Get input until valid
while True:
    height = get_int("Height: ")
    if height < 9 and height > 0:
        break

# Print rows for pyramid
for i in range(height):
    j = i + 1
    print(" " * (height - j) + "#" * j + "  " + "#" * j)