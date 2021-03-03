#!/usr/bin/env python3

import sys


if __name__ == "__main__":
    if ((len(sys.argv) < 2) or (len(sys.argv[1]) != 10)):
        exit()
    param = sys.argv[1]
    try:
        a = int(param[2:4], 16)
        b = int(param[4:6], 16)
        c = int(param[6:8], 16)
        d = int(param[8:10], 16)
    except:
        print("Unvalid value")
        exit()
    result = 0
    up = 0
    for i in [a,b,c,d]:
        if (i > 96 and i < 123):
            index = i - 96
            result += index
        elif (i > 64 and i < 91):
            index = i - 64
            result += index
            up = 104
        else:
            print("Unvalid value")
            exit()
    result += up -4
    if result < 1 or result > 208:
        print("Error")
        exit()
    print(f'offset = {result}')

        