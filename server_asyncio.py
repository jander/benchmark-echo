#!/usr/bin/env python3
#coding=utf-8

"""
code from:
https://docs.python.org/3/library/asyncio-protocol.html#echo-server
"""

import asyncio
#import os

class EchoServer(asyncio.Protocol):
    def connection_made(self, transport):
        self.transport = transport

    def data_received(self, data):
        if data is None:
            return;
        print(type(data))
        self.transport.write(data)


if __name__ == '__main__':
    import sys
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 5000    

    loop = asyncio.get_event_loop()
    coro = loop.create_server(EchoServer, '0.0.0.0', port)
    server = loop.run_until_complete(coro)
    #os.fork()
    print('Starting %s on %d' % ( __file__, port))
    try:
        loop.run_forever()
    except KeyboardInterrupt:
        print("exit")
    finally:
        server.close()
        loop.close()

