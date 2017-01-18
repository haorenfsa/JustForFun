#!/bin/sh

port_start=1025
#for 60 *1000 times
for ((j=0;j<60;j++))
do
	for ((i=0;i<1000;i++))
	do
		let cur_port=$j*1000+$i+$port_start
		curl 127.0.0.1/test -i Connection:keep-alive --local-port $cur_port &
	done
done
