#!/bin/env python3

import sys
import json

def replyParser(commentsDict):
    if bool(commentsDict) is True:
        for i in range(0, len(commentsDict)):
            print(" \__ {0}:\n{1}" .format(commentsDict[i]['author']['name'],
                  commentsDict[i]['text']))
            replyParser(commentsDict[i]['comments'])

def main(argv):
    if len(argv[1:]) != 1:
        print("{0}: More than 1 arg, exit code {1}" .format(argv[0], 2))
        exit(2)

    jsonFileName = argv[1]
    with open(jsonFileName, 'r') as jsonFile:
        jsonDict = json.load(jsonFile)

    for i in range(0, int(jsonDict['size'])):
        if jsonDict['values'][i]['action'] == "COMMENTED":
            try:
                print("\n{0}" .format(jsonDict['values'][i]['commentAnchor']['path']))
            except:
                print("\nNO FILE NAME, PR COMMENTS")

            print("{1}:\n{0}" .format(jsonDict['values'][i]['comment']['text'],
                  jsonDict['values'][i]['comment']['author']['name']))

            replyParser(jsonDict['values'][i]['comment']['comments'])

if __name__ == "__main__":
    main(sys.argv)
