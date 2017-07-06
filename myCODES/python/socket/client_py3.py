#!/usr/bin/env python

import socket


#TCP_IP = '192.168.0.108'
TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024
MESSAGE = "Hello, World!"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.send(MESSAGE.encode(encoding='utf-8'))
data = s.recv(BUFFER_SIZE)
s.close()

print ("received data:", data)