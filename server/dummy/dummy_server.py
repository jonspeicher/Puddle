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

        self.send_response(200)
        self.end_headers()
        varLen = int(self.headers['Content-Length'])
        postVars = self.rfile.read(varLen)
        print postVars

server_address = (SERVER_NAME, SERVER_PORT)
httpd = BaseHTTPServer.HTTPServer(server_address, JsonPostResponder)
httpd.serve_forever()
