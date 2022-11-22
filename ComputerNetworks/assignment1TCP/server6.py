# 6.    The client sends to the server a string and a character.
#       The server returns to the client a list of all positions in the string where specified character is found.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 1234))
sock.listen()

cl_sock, cl_addr = sock.accept()

while True:
    try:
        recv_string = pickle.loads(cl_sock.recv(100))
        if recv_string == "quit":
            cl_sock.close()
            break

        recv_char = pickle.loads(cl_sock.recv(20))

        pos_list = []
        for pos, character in enumerate(recv_string):
            if character == recv_char:
                pos_list.append(pos)

        cl_sock.send(pickle.dumps(pos_list))

    except Exception as e:
        print(f"{e}\n")