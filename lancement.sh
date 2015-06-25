#!/bin/sh
   FILE="$1"
   NAME="${FILE%%.*}"
   EXT="${FILE#*.}"

display_usage() { 
   echo "Usage ./lanchement.sh <fichier.metablocks>"
   } 

if [  $# -eq 0 ] || [ "$EXT" != "metablocks" ]
   then
      display_usage
      exit 1
else

   ./modif.sh "$1"


   wait

   make
   ./main "$NAME.txt"

   wait
   make clean
   rm "$NAME.txt"
   rm "$NAME.xml"

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
      		wait
      		wait
      		wait
      		echo "stop" > /dev/ttyACM0
   	done < test.txt
   fi

fi