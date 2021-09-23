#!/usr/bin/bash

# Set some var's
export WIRE_ALERT="DISCORD_WEBHOOKS_API"

/usr/bin/python3 /home/kite/cronjobs/weeklymediadbalert.py | \
/usr/bin/python3 /home/kite/.bin/wirealert.py &> /dev/null
