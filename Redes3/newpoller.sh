#!/bin/bash

reportar ()
{

swaks --server smtp.gmail.com --port 587 \
	--to $2 \
	--from martin.mimr@gmail.com \
	--auth LOGIN \
	--auth-user martin.mimr@gmail.com \
	--auth-password n0m3l0s3 \
	-tls --attach-type plain/text \
	--attach $1 \
	--header "Subject: Reporte de monitoreo" \
	--body "Hubo algunos problemas con al red.\n Se adjunta un archivo indicando los problemas detectados."

}

typeset -A cfgs
cfgs=(
	[intervalo]=5
	[espera]=2
	[correo]='martin.mimr@gmail.com'
	[ips]='10.0.1.3 10.0.1.4 10.0.1.252 10.0.1.253'
)
# Read configuration file
while read linea
do
	if echo $linea | grep -F = &>/dev/null
	then
		param=$(echo "$linea" | cut -d  "=" -f 1)
		cfgs[$param]=$(echo "$linea" | cut -d "=" -f 2-)
	fi
done < pings.conf

# Change crontab frequency if required
# Check if the entry has already been set
linea=$(grep -E '\*/[0-9]+' /etc/crontab) 
if [ -z "$linea" ]; then
	echo "Ajustando la frecuencia de monitoreo de la red a cada ${cfgs[intervalo]} minutos."
	NEW_CRON='*/'${cfgs[intervalo]}' *   * * *   root    /root/poller.sh'
	echo "$NEW_CRON" >> /etc/crontab
	echo "#" >> /etc/crontab
	echo '¡Hecho!'
	echo "Ahora se realiza el ping a todos los dispositivos en la red cada ${cfgs[intervalo]} minutos."
	#################
else
	OLD_FREQ=$(grep -oE '[0-9]+' <<< "$linea")
	if [ ${cfgs[intervalo]} -ne $OLD_FREQ ]; then
	    echo "Actualizando la frecuencia de monitoreo de la red a cada ${cfgs[intervalo]} minutos."
	    POS=$(($(wc -l /etc/crontab | grep -oE "[0-9]+") - 1))
	    NEW_CRON="\*\/${cfgs[intervalo]} \*   \* \* \*   root    \/root\/poller.sh"
	    SED_COMM=${POS}'s/.*/'${NEW_CRON}'/'
 	    sed -i "$SED_COMM" '/etc/crontab'
	    echo '¡Hecho!'
	    echo "Ahora se realiza el ping a todos los dispositivos en la red cada ${cfgs[intervalo]} minutos."
	#################################
	else
	    echo "La frecuencia de monitoreo ya esta fijada a cada ${cfgs[intervalo]} minutos."
	fi
fi

FECHA=`date +"%d/%m/%Y"`
REPORTE="reporte${FECHA}.txt"
if [ ! -f "$REPORTE" ]; then
    echo "REPORTE DE MONITOREO A LA RED" > $REPORTE
    echo "FECHA:$FECHA" >> $REPORTE
    echo "\n -------------------------------------- \n" >> $REPORTE
fi

ENVIAR=0
LIM=$((${cfgs[espera]} * 1000))
# Ping request to each ip given
for IP in ${cfgs[ips]}
do
	echo "Haciendo ping a dispositivo con ip:$IP"
	resp=$(ping -c 5 -D $IP | cut -d "/" -s -f5)
	if [ -z "$resp" ]; then
	   ENVIAR=1
	   HORA=$(date +"%H:%M:%S")
	   echo "$HORA: El host con ip $IP no se pudo contactar." >> $REPORTE
	elif [ ${resp%.*} -ge $LIM ]; then
	   ENVIAR=1
	   HORA=$(date +"%H:%M:%S")
	   echo "$HORA: El host con ip $IP ha tardado mas de ${cfgs[espera]} seg." >> $REPORTE
        else
	   #echo "Host $IP correcto "
	fi
done

echo "Monitoreo a la red realizado!"

if [ $ENVIAR -eq 1 ]; then
	echo "\n -------------------------------- \n" >> $REPORTE
	echo "Se detectaron problemas con la red."
	echo "Informando al administrador con correo ${cfgs[correo]}"
	reportar $REPORTE ${cfgs[correo]}
fi

