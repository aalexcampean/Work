# 10.   The client sends to the server two strings.
#       The server sends back the character with the largest number of occurrences on the same positions
#       in both strings together with its count.

import socket
import pickle

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(("0.0.0.0", 4567))
    sock.listen()

    cl_sock, cl_addr = sock.accept()

    while True:
        return_string1 = pickle.loads(cl_sock.recv(2000))
        if return_string1 == "quit":
            cl_sock.close()
            break

        return_string2 = pickle.loads(cl_sock.recv(2000))
        print(f"received all data from client\n")

        chars = {}
        if len(return_string1) < len(return_string2):
            s1 = return_string1
            s2 = return_string2
        else:
            s1 = return_string2
            s2 = return_string1

        max_count = 0
        for pos in range(len(s1)):
            if s1[pos] == s2[pos]:
                c = s1[pos]
                if c in chars.keys():
                    chars[c] += 1
                else:
                    chars[c] = 1
                if chars[c] > max_count:
                    max_count = chars[c]

        max_char = ""
        for k in chars.keys():
            if chars[k] == max_count:
                max_char = k

        cl_sock.send(pickle.dumps(max_char))
        cl_sock.send(pickle.dumps(max_count))
        print(f"array sent to client\n")

except Exception as e:
    print(f"{e}\n")