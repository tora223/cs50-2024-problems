from cs50 import get_int

while True:
    height = get_int("Height: ")
    if not (0 < height <= 8):
        print("Please enter a positive integer between 1 and 8.")
    else:
        break

for h in range(height):
    print(" "*(height-h-1) + "#"*(h+1) + "  " + "#"*(h+1))
    