#! /bin/bash

ASN=$1

whois -h  whois.radb.net -- "-i origin $ASN" | \
        tee /tmp/$ASN.whois | \
        grep -oP '([0-9]{1,3}\.){3}([0-9]{1,3})/[0-9][0-9]' | \
        tee /tmp/${ASN}.asn | \
        while read a; do
                iprange $a
        done | tee /tmp/${ASN}.addrs


