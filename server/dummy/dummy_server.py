#!/usr/bin/env python

import BaseHTTPServer

ServerClass = BaseHTTPServer.HTTPServer
RequestHandlerClass = BaseHTTPServer.BaseHTTPRequestHandler

SERVER_NAME = ''
SERVER_PORT = 9000

class JsonPostResponder(RequestHandlerClass):
    def do_POST(self):
        print '---> dummy server: got post!'
        print 'command:', self.command
        print 'path:', self.path
        print 'headers:\n\n', self.headers
        print 'rfile:', self.rfile

server_address = (SERVER_NAME, SERVER_PORT)
httpd = BaseHTTPServer.HTTPServer(server_address, JsonPostResponder)
httpd.serve_forever()
