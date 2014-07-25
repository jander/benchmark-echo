python echo server
==================

use gevent, tornado, twisted, asyncio to build echo sever, and compare their speed.

```
$sh benchmark.sh>benchmark.log 
```

and result on my computer is:

```
c ./server_libev 3100
Throughput: 214467.02 [reqests/sec], errors: 0
Throughput: 220804.31 [reqests/sec], errors: 0
Throughput: 220903.15 [reqests/sec], errors: 0
Throughput: 219720.81 [reqests/sec], errors: 0
Throughput: 225590.31 [reqests/sec], errors: 0

python server_epoll.py 3900
Throughput: 108003.46 [reqests/sec], errors: 0
Throughput: 108214.69 [reqests/sec], errors: 0
Throughput: 108591.34 [reqests/sec], errors: 0
Throughput: 110309.58 [reqests/sec], errors: 0
Throughput: 109282.61 [reqests/sec], errors: 0

python3 server_epoll.py 4000
Throughput: 115253.85 [reqests/sec], errors: 0
Throughput: 115190.78 [reqests/sec], errors: 0
Throughput: 116379.82 [reqests/sec], errors: 0
Throughput: 114897.09 [reqests/sec], errors: 0
Throughput: 112700.61 [reqests/sec], errors: 0

上面的服务器每次连接没有建立协程。

python server_gevent.py 3200
Throughput: 51046.04 [reqests/sec], errors: 0
Throughput: 52686.71 [reqests/sec], errors: 0
Throughput: 51715.62 [reqests/sec], errors: 0
Throughput: 51969.31 [reqests/sec], errors: 0
Throughput: 51036.19 [reqests/sec], errors: 0

python3 server_gevent3.py 3300
Throughput: 85031.97 [reqests/sec], errors: 0
Throughput: 88128.32 [reqests/sec], errors: 0
Throughput: 82256.00 [reqests/sec], errors: 0
Throughput: 81709.07 [reqests/sec], errors: 0
Throughput: 86061.96 [reqests/sec], errors: 0

python server_tornado.py 3400
Throughput: 52252.68 [reqests/sec], errors: 0
Throughput: 52748.79 [reqests/sec], errors: 0
Throughput: 51505.06 [reqests/sec], errors: 0
Throughput: 53063.38 [reqests/sec], errors: 0
Throughput: 51842.82 [reqests/sec], errors: 0

python3 server_tornado.py 3500
Throughput: 47059.97 [reqests/sec], errors: 0
Throughput: 45552.64 [reqests/sec], errors: 0
Throughput: 46548.64 [reqests/sec], errors: 0
Throughput: 46035.63 [reqests/sec], errors: 0
Throughput: 45992.27 [reqests/sec], errors: 0

python server_twisted.py 3600
Throughput: 43411.09 [reqests/sec], errors: 0
Throughput: 42923.03 [reqests/sec], errors: 0
Throughput: 43965.73 [reqests/sec], errors: 0
Throughput: 44171.67 [reqests/sec], errors: 0
Throughput: 43845.68 [reqests/sec], errors: 0

python3 server_twisted.py 3700
Throughput: 40452.62 [reqests/sec], errors: 0
Throughput: 41188.00 [reqests/sec], errors: 0
Throughput: 40992.47 [reqests/sec], errors: 0
Throughput: 40710.83 [reqests/sec], errors: 0
Throughput: 41069.76 [reqests/sec], errors: 0

python3 server_asyncio.py 3800
Throughput: 58291.01 [reqests/sec], errors: 0
Throughput: 58510.31 [reqests/sec], errors: 0
Throughput: 59923.10 [reqests/sec], errors: 0
Throughput: 59477.78 [reqests/sec], errors: 0
Throughput: 59639.14 [reqests/sec], errors: 0
```
