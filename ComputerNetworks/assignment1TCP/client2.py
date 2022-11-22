# 2.    A client sends to the server a string.
#       The server returns the count of spaces in the string.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.2.74", 1234))

while True:
    my_string = input()
    if my_string == "quit":
        sock.send(pickle.dumps("quit"))
        break

    sock.send(pickle.dumps(my_string))
    print(f"sent the string : {my_string}")

    received_data = sock.recv(5)
    nr_of_spaces = pickle.loads(received_data)
    print(f"received the number ({nr_of_spaces}) of spaces found in the sent string")

sock.close()