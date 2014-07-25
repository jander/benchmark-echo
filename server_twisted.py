#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (c) Twisted Matrix Laboratories.
# See LICENSE for details.

from twisted.internet import protocol, reactor


class Echo(protocol.Protocol):
    def dataReceived(self, data):
        """
        As soon as any data is received, write it back.
        """
        self.transport.write(data)


def main():
    import sys
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 5000

    print('Starting %s on %d' % ( __file__, port))

    f = protocol.Factory()
    f.protocol = Echo 
    reactor.listenTCP(port, f, backlog=1024)
    reactor.run()


if __name__ == '__main__':
    main()
