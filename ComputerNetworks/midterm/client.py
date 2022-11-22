# Implement a server application that generates a random integer P and communicates to the clients
# the number of digits of that number – when the client connects.
# Implement a client application that receives from a server the number of digits of P.
# The client generates a random digit every N seconds and sends the digit to the server.
# The server answers with the positions where the digit is found on the server’s number.
# Spawn multiple clients. The server will announce all clients when it has a winner using UDP.
# You should design a method for the server to infer the IP and port
# where is should communicate with each peer over UDP.

import socket
import pickle
import random
import time

if __name__ == "__main__":
    random.seed()
    start = 0
    stop = 2 * 5 - 1

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect(("192.168.2.74", 5545))
    except socket.error as msg:
        print(f"Error: {msg}")
        exit(-1)

    message = pickle.loads(sock.recv(500))
    print(message)

    nr_of_digits = pickle.loads(sock.recv(500))
    print(f"The number should have {nr_of_digits} digits")
    built_number = [None] * nr_of_digits
    finished = False

    while not finished:
        digit_guess = random.randint(start, stop)
        digit_guess = str(digit_guess)
        print('My guess digit: ', digit_guess)
        sock.sendall(pickle.dumps(digit_guess))

        pos = pickle.loads(sock.recv(5000))
        if pos != -1:
            built_number[pos] = digit_guess

            count = 0
            for i in range(nr_of_digits):
                if built_number[count] is None:
                    count += 1
            if count == 0:
                finished = True

            time.sleep(5)

    sock.sendall(pickle.dumps("I finished"))
    message = pickle.loads(sock.recv(1000))
    print(message)
    sock.close()