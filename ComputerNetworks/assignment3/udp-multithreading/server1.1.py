# 1.    A client sends to the server an array of numbers.
#       Server returns the sum of the numbers.

import pickle
import socket
import time

client_count = 0
if __name__ == "__main__":
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(("0.0.0.0", 1234))
    except socket.error as msg:
        print(f"Error: {msg}")
        exit(-1)

    while True:
        buff, addr = sock.recvfrom(2000)
        if pickle.loads(buff) == "quits":
            sock.close()
            break

        arr = pickle.loads(buff)
        arr_sum = sum(arr)

        try:
            print(f"Client #{client_count} from {addr}")
            sock.sendto(pickle.dumps(arr_sum), addr)
        except socket.error as msg:
            print(f"Error: {msg}")
            exit(-1)

        print(f"Client #{client_count} finished")
        client_count += 1

