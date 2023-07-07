from cs50 import get_int

# get numeric input in range
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# for number of rows
for hash in range(1, height + 1):
    # count spaces
    space = height - hash

    # print
    print(' ' * space, end='')
    print('#' * hash, end='')
    print('  ', end='')
    print('#' * hash)
