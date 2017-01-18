#!/bin/sh

for ((;;))
do
	curl 127.0.0.1/_stats > ./myhost.json
	curl -T '/opt/circonus/mymonitors/myhost.json' https://trap.noit.circonus.net/module/httptrap/eb60c547-ddfb-4d5c-8841-dfccec02951a/ft3342080 --insecure
	sleep 10
	echo did1
done
