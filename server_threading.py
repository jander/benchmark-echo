#!/usr/bin/env python
# -*- coding: utf-8 -*-

from SocketServer import ThreadingMixIn, TCPServer, StreamRequestHandler


class TCPHandler(StreamRequestHandler):
    def handle(self):
        while True:
            data = self.rfile.readline()
            if not data:
                break;
            self.wfile.write(data)


class ThreadedTCPServer(ThreadingMixIn, TCPServer):
    pass


if __name__ == '__main__':
    import sys
    port = sys.argv[1] if len(sys.argv) > 1 else 5000

    address = "0.0.0.0", port
    print('Starting tcp server on %s:%d' % address)
    
    server = ThreadedTCPServer(address, TCPHandler)
    server.serve_forever()
