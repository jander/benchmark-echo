python echo server
==================

use gevent, tornado, twisted, asyncio to build echo sever, and compare their speed.

```
$sh benchmark.sh>benchmark.log 
```

and result on my computer is:

```
c ./server_libev 3100
Throughput: 220318.51 [reqests/sec], errors: 0
Throughput: 229591.71 [reqests/sec], errors: 0
Throughput: 222882.07 [reqests/sec], errors: 0
Throughput: 218717.83 [reqests/sec], errors: 0
Throughput: 219586.40 [reqests/sec], errors: 0

python server_epoll.py 3900
Throughput: 109590.47 [reqests/sec], errors: 0
Throughput: 108845.37 [reqests/sec], errors: 0
Throughput: 110208.54 [reqests/sec], errors: 0
Throughput: 109164.47 [reqests/sec], errors: 0
Throughput: 108965.42 [reqests/sec], errors: 0

python3 server_epoll.py 4000
Throughput: 110310.46 [reqests/sec], errors: 0
Throughput: 114583.21 [reqests/sec], errors: 0
Throughput: 112613.40 [reqests/sec], errors: 0
Throughput: 114405.61 [reqests/sec], errors: 0
Throughput: 113342.46 [reqests/sec], errors: 0

上面的服务器每次连接没有建立协程。

python server_gevent.py 3200
Throughput: 51745.78 [reqests/sec], errors: 0
Throughput: 52538.61 [reqests/sec], errors: 0
Throughput: 51979.05 [reqests/sec], errors: 0
Throughput: 51260.55 [reqests/sec], errors: 0
Throughput: 51905.48 [reqests/sec], errors: 0

python3 server_gevent3.py 3300
Throughput: 85005.46 [reqests/sec], errors: 0
Throughput: 84190.32 [reqests/sec], errors: 0
Throughput: 82953.96 [reqests/sec], errors: 0
Throughput: 79926.28 [reqests/sec], errors: 0
Throughput: 86658.78 [reqests/sec], errors: 0

python server_tornado.py 3400
Throughput: 52063.13 [reqests/sec], errors: 0
Throughput: 52443.57 [reqests/sec], errors: 0
Throughput: 51904.25 [reqests/sec], errors: 0
Throughput: 52223.29 [reqests/sec], errors: 0
Throughput: 52933.38 [reqests/sec], errors: 0

python3 server_tornado.py 3500
Throughput: 46416.93 [reqests/sec], errors: 0
Throughput: 46503.64 [reqests/sec], errors: 0
Throughput: 46217.16 [reqests/sec], errors: 0
Throughput: 46085.48 [reqests/sec], errors: 0
Throughput: 43729.05 [reqests/sec], errors: 0

python server_twisted.py 3600
Throughput: 44035.21 [reqests/sec], errors: 0
Throughput: 43664.28 [reqests/sec], errors: 0
Throughput: 43939.14 [reqests/sec], errors: 0
Throughput: 43826.53 [reqests/sec], errors: 0
Throughput: 43730.87 [reqests/sec], errors: 0

python3 server_twisted.py 3700
Throughput: 39074.71 [reqests/sec], errors: 0
Throughput: 40579.55 [reqests/sec], errors: 0
Throughput: 40521.83 [reqests/sec], errors: 0
Throughput: 40183.67 [reqests/sec], errors: 0
Throughput: 40336.90 [reqests/sec], errors: 0

python3 server_asyncio.py 3800
Throughput: 28558.45 [reqests/sec], errors: 0
Throughput: 23892.93 [reqests/sec], errors: 0
Throughput: 23384.66 [reqests/sec], errors: 0
Throughput: 23982.57 [reqests/sec], errors: 0
Throughput: 23812.62 [reqests/sec], errors: 0

```
