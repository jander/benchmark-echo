#!/bin/sh

PARAMS='-t64 -c10 -e10000 -fdata.json'

PORT="$1"
if [ -z "$PORT" ]; then
	PORT=5555
fi

echo "Benchmarking :$PORT"
./client $PARAMS -p$PORT 127.0.0.1
./client $PARAMS -p$PORT 127.0.0.1
./client $PARAMS -p$PORT 127.0.0.1
