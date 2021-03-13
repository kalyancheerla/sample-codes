#!/bin/env python3

import sys

def main():
    # lets assume ax+by=c equation
    # a,b,c as +ve integer constants
    # x, y are +ve integers
    # for known values of a,b,c
    # find all possible values of x and y.
    a,b,c = map(int, input().split())
    # print(a, b, c)
    # lets find range of x
    xmax = c//a
    for xtmp in range(xmax, 0, -1):
        # print(xtmp)
        bytmp = c - (a * xtmp)
        # print(bytmp)
        if (bytmp > 0) and (bytmp % b) == 0:
            print(xtmp, (bytmp//b))

if __name__ == "__main__":
    main()
