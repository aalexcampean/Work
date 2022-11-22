# 1.    A client sends to the server an array of numbers.
#       Server returns the sum of the numbers.

import pickle
import socket
serv = ("192.168.2.74", 6657)

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_D)
    data = input("Provide and array of numbers with format(nr1 nr2 ... nrn): ")
    if data == "quit":
        sock.sendto(pickle.dumps(data), serv)
        sock.close()
    else:
        temp = data.split(" ")
        arr = []
        for t in temp:
            arr.append(int(t))
        sock.sendto(pickle.dumps(arr), serv)

        sum, addr = sock.recvfrom(1000)
        print(f"the sum of the array is {pickle.loads(sum)}, received from {addr}")
        sock.close()

except socket.error as msg:
    print(f"Error: {msg}")
    exit(-1)

