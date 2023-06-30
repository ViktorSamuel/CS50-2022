from cs50 import get_int

# get positive input
while True:
    num = get_int("Card number: ")
    if num > 0:
        break


i = 0
sum = 0
cNum = num
# check aglorithm
while cNum != 0:
    # odd digits
    if (i % 2) != 0:
        digit = (cNum % 10) * 2
        if digit >= 10:
            while digit != 0:
                sum += digit % 10
                digit = int(digit / 10)
        else:
            sum += digit
    # even digit
    else:
        sum += cNum % 10

    cNum = int(cNum / 10)
    i += 1

# if card is valid
if sum % 10 == 0:
    # visa
    if i == 13 and int(num / 1000000000000) == 4:
        print('VISA')
    elif i == 15:
        # amex
        if int(num / 10000000000000) == 34 or int(num / 10000000000000) == 37:
            print('AMEX')
        else:
            print('INVALID')
    elif i == 16:
        # MASTERCARD
        if int(num / 100000000000000) >= 51 and int(num / 100000000000000) <= 55:
            print('MASTERCARD')
        # VISA
        elif int(num / 1000000000000000) == 4:
            print('VISA')
        else:
            print('INVALID')
    else:
        print('INVALID')
else:
    print('INVALID')