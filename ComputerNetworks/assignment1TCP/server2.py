# 2.    A client sends to the server a string.
#       The server returns the count of spaces in the string.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind(("0.0.0.0", 1234))
sock.listen()

c_sock, c_addr = sock.accept()
print("waiting for client to connect")

while True:
    my_string = c_sock.recv(100)
    my_string_data = pickle.loads(my_string)

    if my_string_data == "quit":
        break

    print(f"received the string : {my_string_data}")

    count = my_string_data.count(" ")
    count_data = pickle.dumps(count)

    c_sock.send(count_data)
    print(f"sent the number ({count}) of spaces found in the received string")

c_sock.close()