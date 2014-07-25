#!/usr/bin/env python
# -*- coding: utf-8 -*-

from tornado.ioloop import IOLoop
from tornado.tcpserver import TCPServer


class EchoServer(TCPServer):
    def handle_stream(self, stream, address):
        def on_message(data):
            stream.write_to_fd(data)
            stream.read_until(b'\n', on_message) 

        stream.read_until(b'\n', on_message) 


if __name__ == '__main__':
    import sys
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 5000

    print('Starting %s on %d' % ( __file__, port))
  
    try:
        server = EchoServer()
        server.listen(port)
        #server.bind(port)  
        #server.start(0)
        IOLoop.instance().start()
    except (KeyboardInterrupt, SystemExit):
        print('Exiting...')
    finally:
        IOLoop.instance().stop()
        print("exited cleanly")
