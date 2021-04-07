#!/bin/bash
typeset -A cfgs
cfgs=(
	[intervalo]=5
	[espera]=2
	[correo]='martin.mimr@gmail.com'
	[ips]='10.0.1.3 10.0.1.4 10.0.1.252 10.0.1.253'
)
INTV
WAIT
MAIL
IPS
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
linea=$(grep -n '*/'${cfgs[intervalo]} /etc/crontab | cut -d ':' -s -f1)
if [ -z "$linea" ]; then
	echo "Ajustando la frecuencia de monitoreo de la red a cada ${cfgs[intervalo]} minutos."
	POS=$(($(wc -l /etc/crontab | grep -E -o "[0-9]+") - 1))
	NEW_CRON="\*\/${cgfs[intervalo]} \*  \* \* \* root \/root\/poller.sh"
	SED_COMM=${POS}'s/.*/'${NEW_CRON}'/'
 	sed -i "$SED_COMM" '/etc/crontab'
	echo '¡Hecho!'
	echo "Ahora se realiza el ping a todos los dispositivos en la red cada ${cgfs[intervalo]} minutos."
else 
	echo "La frecuencia de monitoreo ya esta fijada a cada ${cfgs[intervalo]} minutos."
fi

LIM=$(( ${cgfs[ips]}  * 1000))
# Ping request to each ip given
for IP in ${cfgs[ips]}
do
	echo "Haciendo ping a dispositivo con ip:$IP"
	resp=$(ping -c 5 -D $IP | cut -d "/" -s -f5)
	if [ -z "$resp" ]; then
	   echo "Host $IP no disponible informando administrador"
	elif [ ${resp%.*} -ge LIM ]; then
	   echo "Host $IP ha tardado mas de ${cfgs[espera]} seg. informando"
        else
	   echo "Host $IP correcto "
	fi
done

echo "${cfgs[intervalo]}"
echo "${cfgs[espera]}"
echo "${cfgs[correo]}"
