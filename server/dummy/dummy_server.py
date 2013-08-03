#!/usr/bin/env python

import BaseHTTPServer

ServerClass = BaseHTTPServer.HTTPServer
RequestHandlerClass = BaseHTTPServer.BaseHTTPRequestHandler

SERVER_NAME = ''
SERVER_PORT = 9000

class JsonPostResponder(RequestHandlerClass):
    def _get_content_from_stream(self, length, stream):
        return stream.read(length)

    def _transaction_string(self, command, path, headers, content):
        return '%s %s\n%s%s\n' % (command, path, headers, content)

    def _print_request(self, *request):
        print('--> %s' % self._transaction_string(*request))

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        content = self._get_content_from_stream(content_length, self.rfile)
        self._print_request(self.command, self.path, self.headers, content)

        self.send_response(200)
        self.end_headers()

server_address = (SERVER_NAME, SERVER_PORT)
httpd = ServerClass(server_address, JsonPostResponder)
httpd.serve_forever()
