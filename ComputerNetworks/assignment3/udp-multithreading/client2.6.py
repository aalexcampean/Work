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

import socket
import pickle
import random
serv = ("192.168.2.74", 1234)

if __name__ == "__main__":
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as msg:
        print(f"Error: {msg}")
        exit(-1)

    finished = False
    random.seed()
    start = 1
    stop = 2 * 300 - 1
    count = 0
    while not finished:
        my_guess = random.randint(start, stop)
        count += 1
        print(f"My guess is: {my_guess}")

        s.sendto(pickle.dumps(my_guess), serv)
        buff, addr = s.recvfrom(5000)
        answer = pickle.loads(buff)

        if answer == "higher":
            start = my_guess
        elif answer == "lower":
            stop = my_guess
        else:
            print(answer)
            finished = True

    s.close()
