#!/bin/sh

PARAMS='-t2000 -c5 -e1000 -fdata.json'

echo "c ./server_libev 3100"
./client $PARAMS -p3100  127.0.0.1
./client $PARAMS -p3100 127.0.0.1
./client $PARAMS -p3100 127.0.0.1
./client $PARAMS -p3100 127.0.0.1
./client $PARAMS -p3100 127.0.0.1

echo 
echo "python server_epoll.py 3900"
./client $PARAMS -p3900 127.0.0.1
./client $PARAMS -p3900 127.0.0.1
./client $PARAMS -p3900 127.0.0.1
./client $PARAMS -p3900 127.0.0.1
./client $PARAMS -p3900 127.0.0.1

echo 
echo "python3 server_epoll.py 4000"
./client $PARAMS -p4000 127.0.0.1
./client $PARAMS -p4000 127.0.0.1
./client $PARAMS -p4000 127.0.0.1
./client $PARAMS -p4000 127.0.0.1
./client $PARAMS -p4000 127.0.0.1

echo
echo "上面的服务器每次连接没有建立协程。"
echo 
echo "python server_gevent.py 3200"
./client $PARAMS -p3200 127.0.0.1
./client $PARAMS -p3200 127.0.0.1
./client $PARAMS -p3200 127.0.0.1
./client $PARAMS -p3200 127.0.0.1
./client $PARAMS -p3200 127.0.0.1

echo 
echo "python3 server_gevent3.py 3300"
./client $PARAMS -p3300 127.0.0.1
./client $PARAMS -p3300 127.0.0.1
./client $PARAMS -p3300 127.0.0.1
./client $PARAMS -p3300 127.0.0.1
./client $PARAMS -p3300 127.0.0.1

echo 
echo "python server_tornado.py 3400"
./client $PARAMS -p3400 127.0.0.1
./client $PARAMS -p3400 127.0.0.1
./client $PARAMS -p3400 127.0.0.1
./client $PARAMS -p3400 127.0.0.1
./client $PARAMS -p3400 127.0.0.1

echo 
echo "python3 server_tornado.py 3500"
./client $PARAMS -p3500 127.0.0.1
./client $PARAMS -p3500 127.0.0.1
./client $PARAMS -p3500 127.0.0.1
./client $PARAMS -p3500 127.0.0.1
./client $PARAMS -p3500 127.0.0.1

echo 
echo "python server_twisted.py 3600"
./client $PARAMS -p3600 127.0.0.1
./client $PARAMS -p3600 127.0.0.1
./client $PARAMS -p3600 127.0.0.1
./client $PARAMS -p3600 127.0.0.1
./client $PARAMS -p3600 127.0.0.1

echo 
echo "python3 server_twisted.py 3700"
./client $PARAMS -p3700 127.0.0.1
./client $PARAMS -p3700 127.0.0.1
./client $PARAMS -p3700 127.0.0.1
./client $PARAMS -p3700 127.0.0.1
./client $PARAMS -p3700 127.0.0.1

echo 
echo "python3 server_asyncio.py 3800"
./client $PARAMS -p3800 127.0.0.1
./client $PARAMS -p3800 127.0.0.1
./client $PARAMS -p3800 127.0.0.1
./client $PARAMS -p3800 127.0.0.1
./client $PARAMS -p3800 127.0.0.1

