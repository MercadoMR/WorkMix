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

### CHECK IF CVS REPOSITORY EXISTS
CVS='/usr/local/cvsroot'
if [ -d $CVS ]; 
  then
  echo 'El repositorio de cvs fue encontrado';
else
  echo 'El repositorio de cvs no fue encontrado :(';
  echo 'Creandolo...';
  cvs -d $CVS init;
  export CVSROOT=$CVS;
fi

### READ ROUTER'S COMMANDS AND EXECUTE THEM VIA TELNET

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
#CLEAN RETRIEVED ROUTER CONFIGURATION FILE
clean_output $ACTUAL;

### CREATE TODAY PROJECT FOLDER INSIDE THE REPO IF DOESN'T EXIST
FECHA=`date +"%d%m%Y"`
TODAY_PRO="config${FECHA}"
if ! cvs checkout $TODAY_PRO >/dev/null;
   then
	echo "El proyecto de hoy no existe";
	mkdir temprep;
	cp $ACTUAL temprep/
	cd temprep;
        cvs import -m "Created dir for $FECHA configs" $TODAY_PRO mercadomr release1
	cd ..
	rm -r temprep;
	cvs checkout $TODAY_PRO
fi
### CLONE OR UPDATE LOCAL PROJECT FOLDER
if [ ! -d $TODAY_LOC ];
  then
    echo "El directorio de hoy no fue encontrado";
    echo "Clonandolo desde el repositorio";
    cvs checkout $TODAY_LOC;
  else
    cd $TODAY_LOC
    cvs update
    cd ..
fi

