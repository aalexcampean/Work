# and ip address or subnet mask for broadcast
# 192.168.2.255
import os
import re
import struct
import socket
import sys
import time
import datetime
import threading

broad_address = sys.argv[1]
port = 7777
# the key -> (ip, port)
# the value -> (answer, counter_to_responds)
peers_dict = {}
lock = threading.Lock()
number_malformed = 0
malformed_messages = []


def timeQuery(sock: socket.socket):
    while True:
        time.sleep(3)
        print("sent timeQuery")
        sock.sendto(b"TIMEQUERY", (broad_address, port))


def dateQuery(sock: socket.socket):
    while True:
        time.sleep(10)
        print("sent dateQuery")
        sock.sendto(b"DATEQUERY", (broad_address, port))


def receivingThread(sock : socket.socket):
    global number_malformed, malformed_messages
    # waiting from data on that socket
    while True:
        message, from_addr = sock.recvfrom(42, 0)
        message = message.decode()
        if message == "TIMEQUERY":
            time_string = time.strftime("%H:%M:%S")
            time_string = "TIME " + time_string
            # from_addr is a tuple address and port
            sock.sendto(time_string.encode(), from_addr)
            lock.acquire()
            for key in peers_dict.keys():
                peers_dict[key][1] -= 1
                if peers_dict[key][1] == 0:
                    peers_dict.pop(key)
            lock.release()
            continue

        if message == "DATEQUERY":
            date_string = time.strftime("%d:%m:%Y")
            date_string = "DATE " + date_string
            # from_addr is a tuple address and port
            sock.sendto(date_string.encode(), from_addr)
            lock.acquire()
            for key in peers_dict.keys():
                peers_dict[key][1] -= 1
                if peers_dict[key][1] == 0:
                    peers_dict.pop(key)
            lock.release()
            continue

        time_pattern = "TIME [0-9]:[0-9]:[0-9]:[0-9]:[0-9]:[0-9]"
        date_pattern = "DATE [0-9]:[0-9]:[0-9]:[0-9]:[0-9]:[0-9]:[0-9]:0-9"

        if re.search(time_pattern, message) is not None:
            lock.acquire()
            if from_addr not in peers_dict:
                peers_dict[from_addr] = [message, 3]
            else:
                peers_dict[from_addr] = [message, peers_dict[from_addr][1] + 1]
            lock.release()
            continue

        if re.search(date_pattern, message) is not None:
            lock.acquire()
            if from_addr not in peers_dict:
                peers_dict[from_addr] = [message, 3]
            else:
                peers_dict[from_addr] = [message, peers_dict[from_addr][1] + 1]
            lock.release()
            continue

        lock.acquire()
        number_malformed += 1
        malformed_messages.append(message)
        lock.release()


def display():
    while True:
        time.sleep(1)
        os.system('clear')
        lock.acquire()
        print(peers_dict)
        print(malformed_messages)
        lock.release()


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(("", port))

time_query_thread = threading.Thread(target=timeQuery, args=(sock, ))
date_query_thread = threading.Thread(target=dateQuery, args=(sock, ))

receiving_thread = threading.Thread(target=receivingThread, args=(sock, ))
display_thread = threading.Thread(target=display)

time_query_thread.start()
date_query_thread.start()
receiving_thread.start()
display_thread.start()

time_query_thread.join()
date_query_thread.join()
receiving_thread.join()
display_thread.join()
