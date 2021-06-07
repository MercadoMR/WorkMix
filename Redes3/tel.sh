#!/bin/bash

clean_output()
{ 
    #Remove last character for each line
    sed -i 's/.$//' $1 
    #Remove header
    sed -i '1,7d' $1
    #Remove last line
    sed -i '$d' $1
}

find_diffs()
{
    #### CREATE FILE WHO CONTAINS CHANGES MADE
    LINE_NUMBER=$(cvs diff $1 | grep -n diff | cut -f1 -d:)
    cvs diff $1 > $2
    sed -i "1,${LINE_NUMBER}d" $2
    mv $2 ../$2
}

report ()
{
	swaks --server smtp.gmail.com --port 587 -S \
		--to $2 \
		--from martin.mimr@gmail.com \
		--auth LOGIN \
		--auth-user martin.mimr@gmail.com \
		--auth-password "" \
		-tls --attach-type plain/text \
		--attach $1 \
		--header "Subject: Reporte de monitoreo" \
		--body "Hubo algunos problemas con al red.\n Se adjunta un archivo indicando los problemas detectados."

}

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

### CHECK FOR CHANGES
cd $TODAY_LOC
DIFFS='diffs.txt'
SEPARATOR=$(cvs diff $ACTUAL | grep -n diff | cut -f1 -d:)
if [ -n "$SEPARATOR" ]; then
    find_diffs $ACTUAL $DIFFS;
    cd ..
    #### CREATE REPORT FILE IF WAS NOT CREATED PREVIOUSLY
    FECHA=`date +"%d/%m/%Y"`
    FECHA_CAD=$(date +"%d%m%Y")
    REPORTE="changes${FECHA_CAD}.txt"
    if [ ! -f "$REPORTE" ]; then
	    touch $REPORTE
	    echo "REPORTE DE CAMBIOS DETECTADOS" > $REPORTE
	    echo "FECHA: $FECHA" >> $REPORTE
	    echo "Se detectaron cambios en la configuración del router." >> $REPORTE
	    echo "A continuación de muestran los cambios detectados." >> $REPORTE
	    echo "--------------------------------------" >> $REPORTE
    fi
    HORA=$(date +"%H:%M:%S")
    echo "Los siguientes cambios fueron detectados a las $HORA" >> $REPORTE
    cat $DIFFS >> $REPORTE
    echo '--------------------------------------' >> $REPORTE
    CORREO='martin.mimr@gmail.com'
    report $REPORTE $CORREO;
fi
