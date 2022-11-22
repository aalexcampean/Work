# 3.    A client sends to the server a string.
#       The server returns the reversed string to the client (characters from the end to begging)

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.2.74", 1555))

while True:
    read_string = input()
    sock.send(pickle.dumps(read_string))

    if read_string == "quit":
        sock.close()
        break

    inv_string = pickle.loads(sock.recv(50))
    print(f"received inverse string from client {inv_string}\n")