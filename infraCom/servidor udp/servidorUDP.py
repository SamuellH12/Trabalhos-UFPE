from socket import socket, AF_INET, SOCK_DGRAM
from threading import Thread

nome = "SamuellH12"
secretMessage = "Hello! This is a super secret message: \\(^w^)/"

porta = 12210
ip = '127.0.0.1'

sckt = socket(AF_INET, SOCK_DGRAM)
sckt.bind((ip, porta))

print("Server On")

def handleClient(message, addrs):
    message = message.decode()
    print(f"Recive ||| {message} ||| from {addrs}")

    ans = "Hello, Client"

    if message == "homepage":
        ans = "<h1>Hello World</h1>  <h2>This is a Home Page =]</h2>"
    elif message == "name":
        ans = nome
    elif len(message) > 5 and message[:5] == 'lower':
        ans = message[5:].lower()
    elif len(message) > 5 and message[:5] == 'upper':
        ans = message[5:].upper()
    elif message == 'secret code 12210':
        ans = secretMessage
        
    sckt.sendto(ans.encode(), addrs)


while True:
    msg, addrs = sckt.recvfrom(2048)
    Thread(target=handleClient, args=(msg, addrs)).start()