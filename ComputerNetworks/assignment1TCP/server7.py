# 7.    The client sends to the server a string and two numbers (s, I, l).
#       The sever returns to the client the substring of s starting at index I, of length l.

import socket
import pickle

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("0.0.0.0", 1665))
sock.listen()

cl_sock, cl_addr = sock.accept()
while True:
    try:
        inp_string = pickle.loads(cl_sock.recv(100))
        if inp_string == "quit":
            cl_sock.close()
            break

        inp_int1 = pickle.loads(cl_sock.recv(100))
        inp_int2 = pickle.loads(cl_sock.recv(100))
        print("all data received\n")

        subs_string = ""
        count = inp_int2

        for pos in range(inp_int1, len(inp_string)):
            if count == 0:
                break
            subs_string += inp_string[pos]
            count -= 1

        if count != 0:
            subs_string = ""

        cl_sock.send(pickle.dumps(subs_string))
        print("substring sent\n")

    except Exception as e:
        print(f"{e}\n")