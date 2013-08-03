#!/usr/bin/env python

import BaseHTTPServer

ServerClass = BaseHTTPServer.HTTPServer
RequestHandlerClass = BaseHTTPServer.BaseHTTPRequestHandler

SERVER_NAME = ''
SERVER_PORT = 9000

class JsonPostResponder(RequestHandlerClass):
    def _get_content_from_stream(self, length, stream):
        return stream.read(length)

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        content = self._get_content_from_stream(content_length, self.rfile)

        print '\n---> dummy server: got post!'
        print 'command:', self.command
        print 'path:', self.path
        print 'headers:\n\n', self.headers
        print 'content:\n\n', content, '\n'

        self.send_response(200)
        self.end_headers()

server_address = (SERVER_NAME, SERVER_PORT)
httpd = ServerClass(server_address, JsonPostResponder)
httpd.serve_forever()
