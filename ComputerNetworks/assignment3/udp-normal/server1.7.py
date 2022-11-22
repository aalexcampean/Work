# 7.    The client sends to the server a string and two numbers (s, I, l).
#       The sever returns to the client the substring of s starting at index I, of length l.

import socket
import pickle

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("0.0.0.0", 3321))

    buff, addr = sock.recvfrom(1000)
    if pickle.loads(buff) == "quit":
        sock.close()
    else:
        buff1, addr = sock.recvfrom(1000)
        buff2, addr = sock.recvfrom(1000)
        print("all data received\n")

        inp_string = pickle.loads(buff)
        inp_int1 = pickle.loads(buff1)
        inp_int2 = pickle.loads(buff2)

        subs_string = ""
        count = inp_int2

        for pos in range(inp_int1, len(inp_string)):
            if count == 0:
                break
            subs_string += inp_string[pos]
            count -= 1

        if count != 0:
            subs_string = ""

        sock.sendto(pickle.dumps(subs_string), addr)
        print("substring sent\n")

except socket.error as msg:
    print(f"Error: {msg}")
