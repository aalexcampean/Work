# 6.    The client sends to the server a string and a character.
#       The server returns to the client a list of all positions in the string where specified character is found.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.2.74", 1234))

while True:
    try:
        inp_string = input("provide a string: ")
        sock.send(pickle.dumps(inp_string))

        if inp_string == "quit":
            sock.close()
            break

        inp_char = input("provide a char: ")
        sock.send(pickle.dumps(inp_char))

        pos_list = pickle.loads(sock.recv(100))
        print(f"the pos where {inp_char} appears in {inp_string} are: {pos_list}")

    except Exception as e:
        print(f"{e}\n")
