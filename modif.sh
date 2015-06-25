#!/bin/sh

FILE="$1"
NAME="${FILE%%.*}"

rm -f "$NAME.txt"
rm -f "$NAME.xml"

cp "$1" "$NAME.txt"
cp "$1" "$NAME.xml"

./modif_assembleur.sh "$NAME.txt"
./modif_xml.sh "$NAME.xml"
