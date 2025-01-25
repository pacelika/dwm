#!/bin/bash

INTERVAL=5

while true; do
    DATE=$(date +"%Y-%m-%d %I:%M:%S %p")
    LOAD=$(cut -d " " -f1 /proc/loadavg)
    MEM=$(free -h | awk '/^Mem/ {print $3 "/" $2}')
    STATUS="CPU: $LOAD | RAM: $MEM | $DATE"
    xsetroot -name "$STATUS"

    sleep $INTERVAL
done
