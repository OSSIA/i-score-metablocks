#!/bin/sh -x
   f="$1"
   FILE="${f##*/}"
   NAME="${FILE%%.*}"
   EXT="${FILE#*.}"

display_usage() { 
   echo "Usage ./lanchement.sh <fichier.metablocks>"
   } 

if [  $# -eq 0 ] || [ "$EXT" != "metablocks" ]
   then
      #display_usage
      exit 1
else
   script/./modif.sh "$1"
   wait
   make
   function/./main txt/"$NAME.txt"
   wait
   make clean
   wait
   if [ ! -e /dev/ttyACM0 ]
   then
   	echo  "\n=======! No device !=======\n"
   else
   	echo "start" > /dev/ttyACM0
   	while read line  
   	do   
      		echo "$line" > /dev/ttyACM0
      		sleep 100
      		wait
      		echo "stop" > /dev/ttyACM0
   	done < test.txt
   fi
fi