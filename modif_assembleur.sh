#!/bin/sh


sed -i 's/^.*code":"//' "$1"
sed -i 's/","vars.*//' "$1"

sed -i 's/\\n/\n/g' "$1"

sed -i 's/stops/stops \n/g' "$1"
