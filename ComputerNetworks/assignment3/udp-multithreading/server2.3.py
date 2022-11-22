# 3.    The server chooses a random float number <SRF>. Run multiple clients.
#       Each client chooses a random float number <CRF> and send it to the server.
#       When the server does not receive any incoming connection for at least 10 seconds,
#       it chooses the client that has guessed the best approximation (is closest) for its own number and sends it back the message
#       “You have the best guess with an error of <SRV>-<CRF>”.
#       It also sends to each other client the string “You lost !”. The server closes all connections after this.

import socket
import pickle
import random
import sys


def best_guess(values):
    smallest_error = sys.maxsize
    b_guess = 0
    w_client = 0

    for v in values:
        if abs(serv_pick - v[1]) < smallest_error:
            b_guess = v[1]
            w_client = v[0]

    return w_client, b_guess


if __name__ == "__main__":
    while True:
        random.seed()
        start = 0
        stop = 2 * 300 - 1
        serv_pick = random.randint(start, stop)
        clients = []
        client_count = 0
        values = []
        done = False
        winner_client = 0
        winner_guess = None

        print(f"The server picked the number: {serv_pick}")

        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            s.bind(("0.0.0.0", 8123))
        except socket.error as msg:
            print(f"Error: {msg}")
            exit(-1)

        while not done:
            buff, addr = s.recvfrom(1000)
            client_guess = pickle.loads(buff)

            client_count += 1
            print(f"Client #{client_count} guessed {client_guess}")

            values.append([addr, client_guess])
            clients.append(addr)
            if client_count == 3:
                done = True

        if done:
            winner_client, winner_guess = best_guess(values)
            for c in clients:
                if c == winner_client:
                    s.sendto(pickle.dumps(f"You have the best guess with an error of {abs(serv_pick - winner_guess)}"), c)
                else:
                    s.sendto(pickle.dumps(f"You lost !"), c)

            s.close()

