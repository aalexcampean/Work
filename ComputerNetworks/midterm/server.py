# Implement a server application that generates a random integer P and communicates to the clients
# the number of digits of that number – when the client connects.
# Implement a client application that receives from a server the number of digits of P.
# The client generates a random digit every N seconds and sends the digit to the server.
# The server answers with the positions where the digit is found on the server’s number.
# Spawn multiple clients. The server will announce all clients when it has a winner using UDP.
# You should design a method for the server to infer the IP and port
# where is should communicate with each peer over UDP.

import pickle
import socket
import threading
import random
import time

threads = []
thread_count = 0
e = threading.Event()
e.clear()
guessed = False
mutex = threading.Lock()
winner_thread = 0

random.seed()
start = 1
stop = 2**17 - 1
# server_num = random.randint(start, stop)
server_num = 1234
print('Server number: ', server_num)

count = 0
n = server_num
while n > 0:
    count = count + 1
    n = n // 10

count_server_num = count
server_num = str(server_num)


def worker(cl_sock: socket.socket):
    global thread_count, e, guessed, winner_thread, server_num, count_server_num
    my_id = thread_count
    print(f"Connected -- Client# {thread_count} from {cl_sock.getpeername()} {cl_sock}")
    message = f"Hello Client {thread_count} | You are entering the guessing competition!"
    cl_sock.sendall(pickle.dumps(message))

    cl_sock.sendall(pickle.dumps(count_server_num))
    while not guessed:
        try:
            client_guessed_digit = pickle.loads(cl_sock.recv(1000))

            if client_guessed_digit == "I finished":
                mutex.acquire()
                guessed = True
                winner_thread = threading.get_ident()
                mutex.release()
            else:
                pos_in_number = server_num.rfind(client_guessed_digit)
                cl_sock.sendall(pickle.dumps(pos_in_number))

        except socket.error as msg:
            print(f"Error: {msg}")
            break

    if guessed:
        if threading.get_ident() == winner_thread:
            cl_sock.sendall(pickle.dumps(f"You won"))
            print(f"Winner -- Client# {my_id}")
            e.set()
        else:
            cl_sock.sendall(pickle.dumps(f"You lost"))
            print(f"Looser -- Client# {my_id}")

    time.sleep(1)
    cl_sock.close()
    print(f"Disconnected -- Client# {my_id}")


def resetter():
    global threads, thread_count, e, guessed, winner_thread, server_num
    e.wait()
    for t in threads:
        t.join()
    print("All Clients have disconnected")
    e.clear()
    mutex.acquire()
    threads = []
    thread_count = 0
    guessed = False
    winner_thread = 0
    my_num = random.randint(start, stop)
    print('Server number: ', my_num)
    mutex.release()


if __name__ == "__main__":
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind(("0.0.0.0", 5545))
        sock.listen(6)
    except socket.error as msg:
        print(f"Error: {msg}")
        exit(-1)

    reset_t = threading.Thread(target=resetter, daemon=True)
    reset_t.start()

    while True:
        cl_sock, cl_addr = sock.accept()
        worker_t = threading.Thread(target=worker, args=(cl_sock, ))
        threads.append(worker_t)
        thread_count += 1
        worker_t.start()
