# 1.    A client sends to the server an array of numbers.
#       Server returns the sum of the numbers.
import pickle
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.2.74", 5555))

# while True:
#     sock.sendall(input().encode())
#
#     data = sock.recv(20).decode()
#     print(f"the sum of the array is {data}")

while True:
    size = int(input())
    arr = []
    for i in range(size):
        elem = int(input('elem = '))
        arr.append(elem)

    data_string = pickle.dumps(arr)
    sock.send(data_string)

    comp_sum = sock.recv(20)
    data_comp_sum = pickle.loads(comp_sum)
    print(f"the sum of the array is {data_comp_sum}")