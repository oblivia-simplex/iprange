#! /bin/bash

ASN=$1

whois -h  whois.radb.net -- "-i origin $ASN" | \
        tee /tmp/$ASN.whois | \
        grep -oP '([0-9]{1,3}\.){3}([0-9]{1,3})/[0-9][0-9]' | \
        sort | uniq | tee /tmp/${ASN}.cidrs | \
        while read a; do
                iprange $a
        done | sort | uniq | tee /tmp/${ASN}.addrs

echo "IP Address list stored in /tmp/${ASN}.addrs" 1>&2

