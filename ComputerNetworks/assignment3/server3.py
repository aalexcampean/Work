import random
import struct
import socket
import threading

r = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
r.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) #telling to reuse the addrtes if someone is hooked on that one
r.bind(('0.0.0.0', 1234))
r.listen(10)

number = 0
gameOver = False
winner = -1
lock = threading.Lock()
threads = []
finishEvent = threading.Event()


def work(cs):
    while not gameOver:
        c = cs.recv(4) #we need to receive a float so 4 bytes
        c = struct.unpack('!f', c)[0]
        if c > number:
            cs.send(b'S')
        if c < number:
            cs.send(b'H')
        if c == number:
            lock.acquire()
            gameOver = True
            winner = threading.get_ident()
            lock.release()

    if threading.get_ident() == winner:
        cs.send(b'G')
        finishEvent.set()
    else:
        cs.send(b'L')

    cs.close()


def reset():
    global finishEvent, threads, winner, gameOver, number, lock
    while True:
        finishEvent.wait()

        for t in threads:
            t.join()

        lock.acquire()
        winner = -1
        gameover = False
        number = 4
        threads = []
        finishEvent.clear()
        lock.release()


resetThread = threading.Thread(target=reset())
finishEvent.clear()
resetThread.start()


while True:
    (cs, addr) = r.accept()
    thread = threading.Thread(target=work, args=(cs,))
    threads.append(thread)
    thread.start()