# 8.    The client sends to the server two arrays of integers.
#       The server returns an arrays containing the common numbers found in both arrays.

import socket
import pickle

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(("192.168.2.74", 2771))

    while True:
        inp_arr1 = input("provide an array (format: l1 l2 ... ln) / quit to exit: ")
        if inp_arr1 == "quit":
            sock.send(pickle.dumps(inp_arr1))
            break

        inp_arr2 = input("provide a second array (format: l1 l2 ... ln): ")

        arr1_string = inp_arr1.split(" ")
        arr1 = []
        for a in arr1_string:
            arr1.append(int(a))

        arr2_string = inp_arr2.split(" ")
        arr2 = []
        for a in arr2_string:
            arr2.append(int(a))

        sock.send(pickle.dumps(arr1))
        sock.send(pickle.dumps(arr2))

        return_array = pickle.loads(sock.recv(2000))
        print(f"the common values are: {return_array}")

except Exception as e:
    print(f"{e}\n")