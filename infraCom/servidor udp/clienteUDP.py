from socket import socket, AF_INET, SOCK_DGRAM
from threading import Thread

portaServidor = 12210
ipServidor = '127.0.0.1'

sckt = socket(AF_INET, SOCK_DGRAM)

def sendMsg(msg):
    sckt.sendto(msg.encode(), (ipServidor, portaServidor))
    ans, _ = sckt.recvfrom(2048)
    print(f"Server ans:\n{ans.decode()}\n")


# message 1
msg = "Hello, Server!"
print(f"Sending message:\n{msg}")
sendMsg(msg)

# message 2
msg = "lower Hello, Server!"
print(f"Sending message:\n{msg}")
sendMsg(msg)

# message 3
msg = "upper Hello, Server!"
print(f"Sending message:\n{msg}")
sendMsg(msg)

while True:
    msg = input(">>")
    
    if(msg == "exit"):
        break

    sendMsg(msg)

print("exit confirmed")