import socket
import struct

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect(('192.168.2.74', 6666))

    while True:
        sock.sendall(input().encode())
