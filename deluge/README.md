# My deluge headless setup with deluged and deluge-web
---

### Some steps to remember
- Install the deluged and deluge-web from repo's.
    `
    # apt install -y deluged deluge-web
    `
- Get systemctl service files for [deluged](https://github.com/deluge-torrent/deluge/blob/develop/packaging/systemd/deluged.service) and [deluge-web](https://github.com/deluge-torrent/deluge/blob/develop/packaging/systemd/deluge-web.service).
- Update the deluge-web.service file to enable ssl encryption like below.
    `
    ExecStart=/usr/bin/deluge-web -d --ssl
    `
- Add the service user and group fields inside them like below.
    `
    [Service]
    Type=simple
    User=debian-deluged
    Group=debian-deluged
    UMask=007
    `
- Here, we are going to use the already created debian-deluged user/group when installed.
- Copy these 2 edited service files into /etc/systemd/system/ dir.
- Do the daemon-reload as service files got updated.
    `
    $ systemctl daemon-reload
    `
- Check if the service files are enabled by default, if not enable them.
    `
    $ systemctl enable deluged
    $ systemctl enable deluge-web
    `
- Start both the services/daemons.
    `
    $ systemctl start deluged
    $ systemctl start deluge-web
    `
- Go to **https://<ip>:8112** in a browser and type *deluge* for default passwd.
- Update the password.
- Add the global download and upload limit's.
- Enable move completed to a different directory with appropriate permissions like below.
    `
    drwxr-xr-x 2 debian-deluged debian-deluged 4096 May 17 17:56 /torrents
    `
- If it is in a nested dir, check for the executable (x) permission for parent directories.
- Don't use the move completed dir in /root as root dir doesn't have x permission for everyone.
- x permission is required for a directory to enter into it. If it's nested, parent dir's should contain the x too.
- Enable the share ratio option to remove at certain limit.
- Get the **smbuplder.sh** file and move it in the home dir of debian-deluged user (here, /var/lib/deluged/).
- Provide appropriate permissions for the file and also update the file to have correct ip, username and passwd.
- Enable the execute plugin and add the below line for torrent removed.
    `
    /var/lib/deluged/smbuplder.sh
    `
- Do a complete reboot to reflect all these changes.
