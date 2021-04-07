#!/bin/bash
#echo '*/5 *  * * * root /root/poller.sh' >> /root/exam.txt
#echo '#' >> /root/exam.txt

#: <<'EOC' 
#linea=$( cat /root/exam.txt | grep -n '*/5' | cut -d ':' -s -f1)
FREQ=6
linea=$(grep -n '*/'${FREQ} /root/exam.txt | cut -d ':' -s -f1)
if [ -z "$linea" ]; then
	echo "Ajustando la frecuencia de monitoreo de la red a cada $FREQ minutos."
	POS=$(($(wc -l /root/exam.txt | grep -E -o "[0-9]+") - 1))
	echo $POS
	NEW_CRON="\*\/$FREQ \*  \* \* \* root \/root\/poller.sh"
	SED_COMM=${POS}'s/.*/'${NEW_CRON}'/'
        echo "$SED_COMM"
	sed -i "$SED_COMM" '/root/exam.txt'
	echo '¡Hecho!'
	echo "Ahora se realiza el ping a todos los dispositivos en la red cada $FREQ minutos."
else 
	echo "La frecuencia de monitoreo es de cada $FREQ minutos."
	#Command for updating the frequency. An option maybe later available
	#NEW_CRON="\*\/$FREQ \*  \* \* \* root \/root\/poller.sh"
	#SED_COMM=${linea}'s/.*/'${NEW_CRON}'/'
fi
echo 'La linea donde se encontro es:'${linea}

#EOC

