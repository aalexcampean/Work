# 5.    The client sends to the server an integer.
#       The server returns the list of divisors for the specified number.

import pickle
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.2.74", 3333))

while True:
    try:
        inp = input("provide an int number / quit to exit: ")
        sock.send(pickle.dumps(inp))
        if inp == "quit":
            sock.close()
            break

        div_array = pickle.loads(sock.recv(100))
        print(f"the list of divisors for {inp} is: {div_array}")

    except Exception as e:
        print(f"{e}\n")