#!/usr/bin/env python

import BaseHTTPServer

ServerClass = BaseHTTPServer.HTTPServer
RequestHandlerClass = BaseHTTPServer.BaseHTTPRequestHandler

SERVER_NAME = ''
SERVER_PORT = 9000

class JsonPostResponder(RequestHandlerClass):
    def do_POST(self):
        print '\n---> dummy server: got post!'
        print 'command:', self.command
        print 'path:', self.path
        print 'headers:\n\n', self.headers

        content_length = int(self.headers['Content-Length'])
        content = self.rfile.read(content_length)
        print 'content:\n\n', content, '\n'

        self.send_response(200)
        self.end_headers()

server_address = (SERVER_NAME, SERVER_PORT)
httpd = BaseHTTPServer.HTTPServer(server_address, JsonPostResponder)
httpd.serve_forever()
