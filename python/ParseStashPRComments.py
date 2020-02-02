#!/bin/env python

# Import Libraries
import sys     # Req'd for cmd line arg's
import json    # Req'd for parsing json data
import pycurl  # Req'd for python curl functionality

################################################################################
# Function Name: Usage()
#
# Description:
#  Prints the description and usage of the program.
#
# return: <none>
################################################################################
def usage():
    print("\nUsage: ParseStashPRComments <PR-number>")
    print("Connects to stash/bitbucket server REST api and fetches the json"
          " dump of Pull-Request activities, this json dump is parsed to get"
          " the comments and respective Statistics.")
    print("To limit the load on server, once PR#<PR-number>.activities file is"
          " generated it will be used for more than one instance.")
    print("\nEg: ./ParseStashPRComments 1515")
# End of Usage()

################################################################################
# Function Name: getPRActivities()
#
# Description:
#  Function that gets the JSON dump of activities using pycurl functions.
#
# [input] fileName : output File name for JSON dump.
# [input] prNo     : No. of Pull-Request.
#
# return: <none>
################################################################################
def getPRActivities(fileName, prNo):
    # Construct Pull-Request activities URL.
    prURL = "http://127.0.0.1/stash/rest/api/1.0/projects/kalyan/repos/"
    prURL += "sample-codes/pull-requests/"
    prURL += prNo
    prURL += "/activities?limit=1000"

    # Construct Pull-Request activities Headers.
    prAccessToken = "3ZtSQbsH1v0Lkm5YLafuNTe8PWctGAoQxCTF2s50F6FZ"
    prHdr = ['Authorization: Bearer ' + prAccessToken]
    try:
        with open(fileName, "wb") as outfile:
            conn=pycurl.Curl()
            conn.setopt(conn.URL, prURL)
            conn.setopt(conn.HTTPHEADER, prHdr)
            conn.setopt(conn.WRITEDATA, outfile)
            conn.perform()
            conn.close()
    except:
        print("{0}: Error in opening {2} file or cURL getting, rc: {1}"
              .format(argv[0], 5, fileName))
        exit(5)
# End of getPRActivities()

################################################################################
# Function Name: replyParser()
#
# Description:
#  Function that parses the comments dict and it's sub comments dictionaries.
#  comments dictionary is a array of objects and it again contains a comments
#  dictionary. This is a recursive function to simplify the logic.
#
# [input] commentsDict : Dict for comments in
#                        1st comment block in the JSON dump.
#
# return: replyCount : Count for the replies.
################################################################################
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
# End of replyParser()

################################################################################
# Function Name: main()
#
# Description:
#  Function that takes the cmd line argument and checks over them.
#  if PR#<PR-number>.activities exists then try parsing the file.
#  else call the getPRActivities() to generate one.
#
# [input] argv : command line arguments.
#
# return: <none>
#
# Note: This program contains exit codes for any abrupt failure.
################################################################################
def main(argv):
    commentBlocks = 0
    replyCount = 0

    # Check if no. of arguments is 1 or not.
    if len(argv[1:]) != 1:
        print("{0}: Only 1 arg is taken, rc: {1}" .format(argv[0], 2))
        usage()
        exit(2)
    # Check if the argument provided is integer or not.
    if not argv[1].isdigit():
        print("{0}: Argument need to be integer, rc: {1}" .format(argv[0], 3))
        usage()
        exit(3)

    jsonFileName = "PR#" + argv[1] + ".activities"
    # Check if PR#<PR-number>.activities file exists or not.
    try:
        with open(jsonFileName, 'r') as jsonFile:
            jsonDict = json.load(jsonFile)
    except:
        print("{0}: File doesn't exist/Error in JSON parsing" .format(argv[0]))
        # Call cURL function to get the file.
        getPRActivities(jsonFileName, argv[1])
        with open(jsonFileName, 'r') as jsonFile:
            try:
                jsonDict = json.load(jsonFile)
            except:
                print("{0}: Error in JSON parsing, rc: {1}" .format(argv[0], 4))
                exit(4)

    try:
        for i in range(0, int(jsonDict['size'])):
            if jsonDict['values'][i]['action'] == "COMMENTED":
                try:
                    print("\n{0}"
                          .format(jsonDict['values'][i]['commentAnchor']['path']))
                except:
                    print("\nNO FILE NAME, PR COMMENTS")

                commentBlocks = commentBlocks + 1
                print("{0} ({1}):\n{2}"
                      .format(jsonDict['values'][i]['comment']['author']['name'],
                              jsonDict['values'][i]['comment']['author']['displayName'],
                              jsonDict['values'][i]['comment']['text']))

                replyCount += replyParser(jsonDict['values'][i]['comment']['comments'])
    except:
        print("{0}: Maybe JSON data structure is different, rc: {1}"
              .format(argv[0], 6))
        exit(6)

    print("\n\nSTATS:\nNo. of comments is {0}" .format(replyCount + commentBlocks))
#End of main()

if __name__ == "__main__":
    main(sys.argv)
