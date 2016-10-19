#! /bin/bash

curl ipinfo.io | grep -oP '(?<=org\":\s\")[A-Za-z0-9]+' | xargs ./asn.sh 

