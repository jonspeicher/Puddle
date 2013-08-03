#!/usr/bin/env python

import BaseHTTPServer

ServerClass = BaseHTTPServer.HTTPServer
RequestHandlerClass = BaseHTTPServer.BaseHTTPRequestHandler

SERVER_NAME = ''
SERVER_PORT = 9000

class JsonPostResponder(RequestHandlerClass):
    def _get_requested_filename(self, path):
        return '.' + path

    def _get_content_from_stream(self, length, stream):
        return stream.read(length)

    def _get_content_from_file(self, filename):
        content = ''
        with open(filename, 'r') as content_file:
            content = content_file.read()
        return content

    def _send_response(self, status, content):
        self.send_response(status)
        self.end_headers()
        self.wfile.write(content)

    def _print_request(self, command, path, headers, content):
        print('\n%s --> %s\n%s%s\n' % (command, path, headers, content))

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        content = self._get_content_from_stream(content_length, self.rfile)
        self._print_request(self.command, self.path, self.headers, content)

        filename = self._get_requested_filename(self.path)
        content = self._get_content_from_file(filename)
        self._send_response(200, content)
        print content

server_address = (SERVER_NAME, SERVER_PORT)
httpd = ServerClass(server_address, JsonPostResponder)
httpd.serve_forever()
