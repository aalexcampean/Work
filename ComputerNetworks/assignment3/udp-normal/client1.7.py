# 7.    The client sends to the server a string and two numbers (s, I, l).
#       The sever returns to the client the substring of s starting at index I, of length l.

import socket
import pickle
serv = ("192.168.2.74", 3321)

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    inp_string = input("provide a string / quit for exit: ")
    sock.sendto(pickle.dumps(inp_string), serv)

    if inp_string == "quit":
        sock.close()
    else:
        inp_int1 = int(input("provide the first integer: "))
        inp_int2 = int(input("provide the second integer: "))
        sock.sendto(pickle.dumps(inp_int1), serv)
        sock.sendto(pickle.dumps(inp_int2), serv)

        buff, addr = sock.recvfrom(100)
        recv_sub_string = pickle.loads(buff)
        print(recv_sub_string)
        if not recv_sub_string:
            print(
                f"the substring of |{inp_string}| starting from pos |{inp_int1}| of length |{inp_int2}| cannot be obtained\n")
        else:
            print(
                f"the substring of |{inp_string}| starting from pos |{inp_int1}| of length |{inp_int2}| is |{recv_sub_string}|\n")

except socket.error as msg:
    print(f"Error: {msg}")
    exit(-1)