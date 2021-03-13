#!/bin/env python3

import sys

def main():
    # lets assume ax+by+cz=d equation
    # a,b,c,d as +ve integer constants
    # x, y, z are +ve integers
    # for known values of a,b,c,d
    # find all possible values of x y & z.
    a,b,c,d = map(int, input().split())
    # print(a, b, c, d)
    # lets find range of x
    xmax = d//a
    for xtmp in range(xmax, 0, -1):
        tmp1 = d - (a * xtmp)
        ymax = tmp1//b
        for ytmp in range(ymax, 0, -1):
            tmp2 = tmp1 - (b * ytmp)
            if (tmp2 > 0) and ((tmp2 % c) == 0):
                print(xtmp, ytmp, tmp2//c)

if __name__ == "__main__":
    main()
