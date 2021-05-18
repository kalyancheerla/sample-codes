#!/bin/bash

################################################################################
# Get some details from the execute command
# $1 ---> Torrent Id
# $2 ---> Torrent Name
# $3 ---> Torrent Path
################################################################################
torrent_downloads="$3"
filename="$2"
torrentid="$1"

################################################################################
# SAMBA share details
################################################################################
smbusr="user%passwd"
smbip="//<ip>/videos/"
smbloc="New"

################################################################################
# Log file and other param's
################################################################################
completedpath="torrents"
logfile="/tmp/smbuplder_$(printf "${torrentid}" | cut -c-5).log"
retCd=0
rc=0

################################################################################
# Main(): Starts here
################################################################################
# reset logfile
> "${logfile}"
echo "Logging starts here..." >> "${logfile}"
echo "${torrent_downloads}/${filename}" >> "${logfile}"

# filename exists at given path and regular file
# and also it is in the completed path, not any path.
if [ -f "${torrent_downloads}/${filename}" -a \
     $(basename "${torrent_downloads}") = "${completedpath}" ]
then
    # filename has matching regex
    if [[ "${filename}" =~ ^[[:alnum:]\.]*[Mm]ovie[Rr]ulz ]]
    then
        # get new name by removing the regex matching part
        newfilename=$(printf "${filename}" | cut -d ' ' -f 3-)
    else
        newfilename="${filename}"
    fi
    echo "New filename: ${newfilename}" >> "${logfile}"

    # upload the file with new filename
    smbcmd="put \"${torrent_downloads}/${filename}\" \"${newfilename}\""
    smbclient -U "${smbusr}" "${smbip}" --directory "${smbloc}" \
              -c "${smbcmd}" &>> "${logfile}"
    rc="$?"

    # On success of smbclient, remove the file
    if [ "${rc}" -eq 0 ]
    then
        rm "${torrent_downloads}/${filename}" &>> "${logfile}"
    else
        echo "smbclient ${filename} failed with rc=${rc}" >> "${logfile}"
    fi
else
    echo "Maybe its not in the completed path" >> "${logfile}"
    echo "Maybe its a dir, yet to work on that..." >> "${logfile}"
fi

echo "Logging ends here..." >> "${logfile}"
exit "${retCd}"
################################################################################
# Main(): Ends here
################################################################################
