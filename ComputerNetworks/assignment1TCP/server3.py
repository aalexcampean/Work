# 3.    A client sends to the server a string.
#       The server returns the reversed string to the client (characters from the end to begging)

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 1555))
sock.listen()

cl_sock, cl_addr = sock.accept()

while True:
    recv_string = pickle.loads(cl_sock.recv(50))
    # if not recv_string:
    #     print("nothing was sent by the client")
    #     break

    if recv_string == "quit":
        cl_sock.close()
        break

    print(f"received string from client\n")

    rev_recv_string = recv_string[::-1]

    cl_sock.send(pickle.dumps(rev_recv_string))
    print(f"sent the reverse string to client\n")


