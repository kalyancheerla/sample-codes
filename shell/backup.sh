#!/bin/bash

DATE=$(date +%d-%m-%Y)
BACKUP_DIR="/media/kalyan/Backup"

#To backup $USER home directory
tar -zcvpf $BACKUP_DIR/$USER-$DATE.tar.gz /home/$USER
