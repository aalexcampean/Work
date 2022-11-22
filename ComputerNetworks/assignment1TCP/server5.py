# 5.    The client sends to the server an integer.
#       The server returns the list of divisors for the specified number.

import pickle
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 3333))
sock.listen()

cl_sock, cl_addr = sock.accept()

while True:
    try:
        inp = pickle.loads(cl_sock.recv(100))
        if inp == "quit":
            cl_sock.close()
            break
        n = int(inp)

        div_arr = []
        for x in range(1, n//2 + 1):
            if n % x == 0:
                div_arr.append(x)
        div_arr.append(n)
        print(div_arr)
        cl_sock.send(pickle.dumps(div_arr))

    except Exception as e:
        print(f"{e}\n")