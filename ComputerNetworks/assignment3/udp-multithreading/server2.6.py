# 6.    The server chooses a random integer number.
#       Each client generates a random integer number and send it to the server.
#       The server answers with the message “larger” if the client has sent a smaller number
#       than the server’s choice, or with message “smaller” if the client has send a larger number
#       than the server’s choice. Each client continues generating a different random number
#       (larger or smaller than the previous) according to the server’s indication.
#       When a client guesses the server choice – the server sends back to the winner the message
#       “You win – within x tries”. It also sends back to all other clients the message
#       “You lost – after y retries!” (x and y are the number of tries of each respective client).
#       The server closes all connections upon a win and it chooses
#       a different random integer for the next game (set of clients)
import collections
import pickle
import socket
import threading
import random
import time

if __name__ == "__main__":
    while True:
        random.seed()
        start = 1
        stop = 2 * 300 - 1
        clients = []
        server_num = random.randint(start, stop)

        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            s.bind(("0.0.0.0", 1234))
        except socket.error as msg:
            print(f"Error: {msg}")
            exit(-1)

        guessed = False
        while not guessed:
            buff, addr = s.recvfrom(1000)
            clients.append(addr)
            client_guess = pickle.loads(buff)

            if client_guess < server_num:
                s.sendto(pickle.dumps("higher"), addr)
            elif client_guess > server_num:
                s.sendto(pickle.dumps("lower"), addr)
            else:
                guessed = True
                winner_thread = addr

        if guessed:
            checked_clients = []
            for c in clients:
                if c not in checked_clients:
                    if c == winner_thread:
                        s.sendto(pickle.dumps(f"You won – within {clients.count(c)} tries"), c)
                        print(f"Winner -- Client# {c}")
                    else:
                        s.sendto(pickle.dumps(f"You lost – after {clients.count(c)} retries!"), c)
                        print(f"Looser -- Client# {c}")
                    checked_clients.append(c)
            s.close()
