# 4.    The client send to the server two sorted array of chars.
#       The server will merge sort the two arrays and return the result to the client.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.2.74", 2111))

while True:
    try:
        string_arr1 = input("provide 2 arrays with format (l1 l2 l3 ... ln) : \n")
        if string_arr1 == "quit":
            sock.send(pickle.dumps(string_arr1))
            sock.close()
            break
        string_arr2 = input()

        # transforming the string input into an actual array
        arr1 = string_arr1.split(" ")
        arr2 = string_arr2.split(" ")

        # sorting the arrays
        arr1.sort()
        arr2.sort()

        # sending the arrays in
        sock.send(pickle.dumps(arr1))
        sock.send(pickle.dumps(arr2))

        merged_array = pickle.loads(sock.recv(100))
        print(f"the merge sorted result array is {merged_array}")

    except Exception as e:
        print(f"{e}\n")
