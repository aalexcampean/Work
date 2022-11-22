# 10.   The client sends to the server two strings.
#       The server sends back the character with the largest number of occurrences on the same positions
#       in both strings together with its count.

import socket
import pickle

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(("192.168.2.74", 4567))

    while True:
        inp_string1 = input("provide an string / quit to exit: ")
        if inp_string1 == "quit":
            sock.send(pickle.dumps(inp_string1))
            break

        inp_string2 = input("provide a second string: ")

        sock.send(pickle.dumps(inp_string1))
        sock.send(pickle.dumps(inp_string2))

        return_char = pickle.loads(sock.recv(2000))
        return_count = pickle.loads(sock.recv(2000))
        print(f"the char with the largest nr of occurrences of {return_count} is {return_char}")

except Exception as e:
    print(f"{e}\n")