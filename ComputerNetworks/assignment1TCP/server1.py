# 1.    A client sends to the server an array of numbers.
#       Server returns the sum of the numbers.
import pickle
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind(("0.0.0.0", 5555))
sock.listen()

c_sock, c_addr = sock.accept()

print("waiting for client to connect")
# while True:
#     data = c_sock.recv(20).decode()
#     if not data:
#         print("nothing was sent by the client")
#         break
#
#     print(f"received {data}")
#     numbers = data.split(" ")
#     numSum = 0
#     try:
#         for n in numbers:
#             numSum += int(n)
#     except Exception as e:
#         print(e)
#
#     numSum = str(numSum)
#     c_sock.sendall(numSum.encode())
#     print(f"sent {numSum}")
#
# c_sock.close()

while True:
    arr = c_sock.recv(1000)
    data_arr = pickle.loads(arr)
    if not data_arr:
        print("nothing was sent by the client")
        break

    print(f"the array received {data_arr}")
    numSum = 0
    for n in data_arr:
        numSum += n

    data_numSum = pickle.dumps(numSum)
    c_sock.sendall(data_numSum)
    print(f"sent {numSum}")

c_sock.close()
