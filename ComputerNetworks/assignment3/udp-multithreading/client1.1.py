# 1.    A client sends to the server an array of numbers.
#       Server returns the sum of the numbers.

import pickle
import socket
import time
serv = ("192.168.2.74", 1234)

if __name__ == "__main__":
    while True:
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        except socket.error as msg:
            print(f"Error {msg}")
            exit(-1)

        try:
            data = input("Provide and array of numbers with format(nr1 nr2 ... nrn): ")
            if data == "quit":
                sock.sendto(pickle.dumps(data), serv)
                sock.close()
                break
            else:
                temp = data.split(" ")
                arr = []
                for t in temp:
                    arr.append(int(t))
                sock.sendto(pickle.dumps(arr), serv)

                sum, addr = sock.recvfrom(1000)
                print(f"the sum of the array is {pickle.loads(sum)}, received from {addr}")
                sock.close()
                break

        except socket.error as msg:
            print(f"Error {msg}")
            sock.close()
            exit(-1)
