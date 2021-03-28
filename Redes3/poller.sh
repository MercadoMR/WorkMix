#!/bin/bash
typeset -A cfgs
cfgs=(
	[intervalo]=5
	[espera]=2
	[correo]='martin.mimr@gmail.com'
	[ips]='10.0.1.3 10.0.1.4 10.0.1.252 10.0.1.253'
)

while read linea
do
	if echo $linea | grep -F = &>/dev/null
	then
		param=$(echo "$linea" | cut -d  "=" -f 1)
		cfgs[$param]=$(echo "$linea" | cut -d "=" -f 2-)
	fi
done < pings.conf

for IP in ${cfgs[ips]}
do
	echo $IP
done

echo "${cfgs[intervalo]}"
echo "${cfgs[espera]}"
echo "${cfgs[correo]}"
