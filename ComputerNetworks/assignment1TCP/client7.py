# 7.    The client sends to the server a string and two numbers (s, I, l).
#       The sever returns to the client the substring of s starting at index I, of length l.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.2.74", 1665))

while True:
    try:
        inp_string = input("provide a string / quit for exit: ")
        sock.send(pickle.dumps(inp_string))

        if inp_string == "quit":
            sock.close()
            break

        inp_int1 = int(input("provide the first integer: "))
        inp_int2 = int(input("provide the second integer: "))
        sock.send(pickle.dumps(inp_int1))
        sock.send(pickle.dumps(inp_int2))

        recv_sub_string = pickle.loads(sock.recv(100))
        print(recv_sub_string)
        if not recv_sub_string:
            print(f"the substring of |{inp_string}| starting from pos |{inp_int1}| of length |{inp_int2}| cannot be obtained\n")
        else:
            print(f"the substring of |{inp_string}| starting from pos |{inp_int1}| of length |{inp_int2}| is |{recv_sub_string}|\n")

    except Exception as e:
        print(f"{e}\n")