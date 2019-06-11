#!/usr/bin/python3
import cgi
import socket
import sys
import os
import json
import urllib

print('Content-Type: text/html\n')

form = cgi.FieldStorage()

if 'text' not in form:
    print('???')
    sys.exit(1)
else: text = form['text'].value
if 'color' not in form:
    color = '#FFFFFF'
else: color = form['color'].value
if 'font' not in form:
    font = ''
else: font = form['font'].value

data = json.dumps({ 
                    'text': text[:80],
                    'color': color,
                    'font': font
                  })
print("<html><head>")
print("<meta http-equiv=\"refresh\" content=\"5;url=/?color={}&font={}\"/>".format(urllib.parse.quote(color), font))
print("</head><body>")
print("Received data, redirecting...")
print("</body></html>")
server_address = '/home/will/led-site/serv_socket'
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)


try:
    sock.connect(server_address)
    sock.sendall(data.encode('utf-8'))
except socket.error as err:
    sys.stderr.write(str(err) + "\n")
