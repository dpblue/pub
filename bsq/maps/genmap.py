import random
import sys

if len(sys.argv) != 4:
    sys.exit("program x y density")
x, y, density = map(int, sys.argv[1:])
print(f"{y}.ox")
for i in range(y):
    for j in range(x):
        if int(random.random() * 2 * y) < density:
            print("o", end="")
        else:
            print(".", end="")
    print()
