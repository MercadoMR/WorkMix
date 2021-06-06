#!/bin/bash

clean_output()
{ 
    #Remove last character for each line
    sed -i 's/.$//' $1 
    #Remove header
    sed -i '1,7d' $1
    #Remove last line
    sed -i '$d' $1
};

CVSROOT='/usr/local/cvsroot'

if [ -d $CVSROOT ]; 
  then
  echo 'El repositorio de cvs fue encontrado';
else
  echo 'El repositorio de cvs no fue encontrado :(';
  echo 'Creandolo...';
  cvs -d $CVSROOT init;
  export CVSROOT=$CVSROOT;

fi

ACTUAL=running-config.txt
COMANDOS=comandos.txt
ROUTER=10.0.8.254
while read comando 
  do
  {
      sleep 1;
      echo "$comando";
  }
done < $COMANDOS | telnet $ROUTER > $ACTUAL

clean_output $ACTUAL;



