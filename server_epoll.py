#!/usr/bin/env python
#coding=utf-8

import socket, select
import sys


BUFFER_SIZE = 10240

port = int(sys.argv[1]) if len(sys.argv) > 1 else 5000

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('0.0.0.0', port))
server.listen(1024)
server.setblocking(0)

print('Starting %s on :%d' % ( __file__, port))

epoll = select.epoll()
epoll.register(server.fileno(), select.EPOLLIN)

try:
    connections = {}; buffers = {}
    while True:
        events = epoll.poll(1)
        for fileno, event in events:
            if fileno == server.fileno():
                conn, address = server.accept()
                conn.setblocking(0)
                epoll.register(conn.fileno(), select.EPOLLIN)
                connections[conn.fileno()] = conn
                buffers[conn.fileno()] = b''

            elif event & select.EPOLLIN:
                buffers[fileno] += connections[fileno].recv(BUFFER_SIZE)

                if len(buffers[fileno]) == 0:
                    epoll.modify(fileno, 0)
                    connections[fileno].shutdown(socket.SHUT_RDWR)
                else:
                    epoll.modify(fileno, select.EPOLLOUT)

            elif event & select.EPOLLOUT:
                sent = connections[fileno].send(buffers[fileno])
                buffers[fileno] = buffers[fileno][sent:]

                if len(buffers[fileno]) == 0:
                    epoll.modify(fileno, select.EPOLLIN | select.EPOLLOUT)

            elif event & select.EPOLLHUP:
                epoll.unregister(fileno)
                connections[fileno].close()
                del connections[fileno]
finally:
    epoll.unregister(server.fileno())
    epoll.close()
    server.close()