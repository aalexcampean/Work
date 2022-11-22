import socket
import struct

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind(("0.0.0.0", 6666))
sock.listen()

client_sock, client_address = sock.accept()

print("waiting...")
while True:
    data = client_sock.recv(10)
    if not data:
        print("didn't receive anything")
        break

    print(f"received {data.decode()}")

