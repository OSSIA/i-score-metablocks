#!/bin/sh

f="$1"
FILE="${f##*/}"
NAME="${FILE%%.*}"

rm -f "$NAME.txt"
rm -f "$NAME.xml"

cp "$1" "$NAME.txt"
cp "$1" "$NAME.xml"

script/./modif_assembleur.sh "$NAME.txt"
script/./modif_xml.sh "$NAME.xml"

wait

mv "$NAME.txt" txt/
mv "$NAME.xml" xml/
