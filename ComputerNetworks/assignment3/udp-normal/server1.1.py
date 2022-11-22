# 1.    A client sends to the server an array of numbers.
#       Server returns the sum of the numbers.

import pickle
import socket

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("0.0.0.0", 6657))

    buff, addr = sock.recvfrom(1000)
    if pickle.loads(buff) == "quit":
        print("The Client quit")
        sock.close()
    else :
        arr_sum = sum(pickle.loads(buff))
        sock.sendto(pickle.dumps(arr_sum), addr)
        sock.close()

except socket.error as msg:
    print(f"Error: {msg}")
    exit(-1)