# 8.    The client sends to the server two arrays of integers.
#       The server returns an arrays containing the common numbers found in both arrays.

import socket
import pickle

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(("0.0.0.0", 2771))
    sock.listen()

    cl_sock, cl_addr = sock.accept()

    while True:
        return_array1 = pickle.loads(cl_sock.recv(2000))
        if isinstance(return_array1, str) and return_array1 == "quit":
            cl_sock.close()
            break

        return_array2 = pickle.loads(cl_sock.recv(2000))
        print(f"received all data from client\n")

        comm_array = []
        for elem in return_array1:
            if elem in return_array2:
                comm_array.append(elem)

        cl_sock.send(pickle.dumps(comm_array))
        print(f"array sent to client\n")

except Exception as e:
    print(f"{e}\n")