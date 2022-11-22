# 4.    The client send to the server two sorted array of chars.
#       The server will merge sort the two arrays and return the result to the client.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 2111))
sock.listen()

cl_sock, cl_addr = sock.accept()

while True:
    try:
        arr1 = pickle.loads(cl_sock.recv(100))
        if arr1 == "quit":
            cl_sock.close()
            break
        arr2 = pickle.loads(cl_sock.recv(100))

        arr = arr1 + arr2
        arr.sort()
        cl_sock.send(pickle.dumps(arr))

    except Exception as e:
        print(f"{e}\n")