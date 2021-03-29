#========================================================
#A script for setting static networking configurations on the TinyCore VM
#I am using the script shown in https://iotbytes.wordpress.com/assign-persistent-static-ip-address-to-microcore-tiny-linux/ as my reference
#With with my particular modifcations
#!/bin/sh
# kill dhcp client for eth0
if [ -f /var/run/udhcpc.eth0.pid ]; then
kill `cat /var/run/udhcpc.eth0.pid`
sleep 0.1
fi
# Configure interface eth0
ifconfig eth0 10.0.1.3 netmask 255.255.255.0 broadcast 10.0.1.255 up
route add default gw 10.0.1.254
echo nameserver 8.8.8.8 >> /etc/resolv.conf
#========================================================
