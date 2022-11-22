# 3.    The server chooses a random float number <SRF>. Run multiple clients.
#       Each client chooses a random float number <CRF> and send it to the server.
#       When the server does not receive any incoming connection for at least 10 seconds,
#       it chooses the client that has guessed the best approximation (is closest) for its own number and sends it back the message
#       “You have the best guess with an error of <SRV>-<CRF>”.
#       It also sends to each other client the string “You lost !”. The server closes all connections after this.

import socket
import pickle
import random
serv = ("192.168.2.74", 8123)

if __name__ == "__main__":
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as msg:
        print(f"Error: {msg}")
        exit(-1)

    random.seed()
    start = 1
    stop = 2 * 300 - 1

    my_guess = random.randint(start, stop)
    print(f"My guess is: {my_guess}")
    s.sendto(pickle.dumps(my_guess), serv)

    buff, addr = s.recvfrom(1000)
    print(pickle.loads(buff))
