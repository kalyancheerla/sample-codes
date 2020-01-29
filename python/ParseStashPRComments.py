#!/bin/env python3

import sys
import json

def main(argv):
    if len(argv[1:]) != 1:
        print("{0}: More than 1 arg, exit code {1}" .format(argv[0], 2))
        exit(2)

    jsonFileName = argv[1]
    with open(jsonFileName, 'r') as jsonFile:
        jsonDict = json.load(jsonFile)

    for i in range(0, int(jsonDict['size'])):
        if jsonDict['values'][i]['action'] == "COMMENTED":
            print("{1}: {0}" .format(jsonDict['values'][i]['comment']['text'],
                  jsonDict['values'][i]['comment']['author']['name']))

            for j in range(0, len(jsonDict['values'][i]['comment']['comments'])):
                print(" \__ {1}: {0}"
                .format(jsonDict['values'][i]['comment']['comments'][j]['text'],
                jsonDict['values'][i]['comment']['comments'][j]['author']['name']))

if __name__ == "__main__":
    main(sys.argv)
