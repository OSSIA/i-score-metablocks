#!/bin/sh

sed -i 's/\\"/"/g' "$1"
sed -i 's/xhtml">/xhtml">\n/g' "$1"
sed -i '/^.*xhtml">/d' "$1"
sed -i 's/","code.*//' "$1"
sed -i 's/<\/xml>//g' "$1"

xmllint --format "$1" > tmp.xml
mv tmp.xml "$1"
