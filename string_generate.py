#!/usr/bin/env python3

import string


def listAlphabet():
    for i in string.ascii_lowercase:
        print(i*4, end='')
    for i in string.ascii_uppercase:
        print(i*4, end='')

if __name__ == "__main__":
    listAlphabet()
