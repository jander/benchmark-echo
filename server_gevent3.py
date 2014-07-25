#!/usr/bin/env python3
#coding=utf-8

import gevent
from gevent import socket
from gevent.server import StreamServer

def start_server(address, handle_func):
    server = StreamServer(address, handle_func, spawn=2000, backlog=1024)
    print('Starting %s on %r' % ( __file__, address))

    try:
        server.serve_forever()
    except (KeyboardInterrupt, SystemExit):
        print('Exiting...')
    finally:
        print('stop server...')
        server.stop()


def on_handle(socket, address):
    try:
        fileobj = socket.makefile() #encoding="utf-8", errors="ignore"
        while True:
            data = fileobj.readline()
            if not data:
                # client disconnected
                break            
            socket.sendall(bytes(data, "utf-8"))
    finally:
        socket.close()


if __name__ == '__main__':
    import sys
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 5000

    start_server(("0.0.0.0", port), on_handle)