#!/bin/env python

import sys
import json

def replyParser(commentsDict):
    replyCount = 0
    funcRc = 0
    if bool(commentsDict) is True:
        for i in range(0, len(commentsDict)):
            replyCount = replyCount + 1
            print(" \__ {0} ({1}):\n{2}"
                  .format(commentsDict[i]['author']['name'],
                          commentsDict[i]['author']['displayName'],
                          commentsDict[i]['text']))
            funcRc = replyParser(commentsDict[i]['comments'])
    return (replyCount + funcRc)

def main(argv):
    commentBlocks = 0
    replyCount = 0
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

            commentBlocks = commentBlocks + 1
            print("{0} ({1}):\n{2}"
                  .format(jsonDict['values'][i]['comment']['author']['name'],
                          jsonDict['values'][i]['comment']['author']['displayName'],
                          jsonDict['values'][i]['comment']['text']))

            replyCount += replyParser(jsonDict['values'][i]['comment']['comments'])

    print("\n\nSTATS:\nNo. of comments is {0}" .format(replyCount + commentBlocks))

if __name__ == "__main__":
    main(sys.argv)
