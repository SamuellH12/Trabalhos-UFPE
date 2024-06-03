from socket import socket, AF_INET, SOCK_STREAM
from threading import Thread

ip = input("ip >> ")
porta = int(input("port >> "))

if len(ip) == 0:
    ip = '127.0.0.1'

print(ip, porta)

peer = socket(AF_INET, SOCK_STREAM)
peer.bind((ip, porta))


def handleRequest(client, clientAddress):
    print("cliente conectado: ", clientAddress)
    while True:
        data = client.recv(2048).decode()
        print(f"Recive from {clientAddress} >> {data}")


        if data == 'exit':
            print(f"Encerrando conexão com {clientAddress}")
            break
        elif data == 'ping':
            resp = "pong"
            client.send(resp.encode())


def servidor():
    peer.listen()

    while True:
        clienteSocket, clienteAddress = peer.accept()

        Thread(target=handleRequest, args=(clienteSocket, clienteAddress)).start()





# Cria a thread do Servidor
Thread(target=servidor, args=()).start()

###########################################
# CLIENTE
###########################################

ipServidor = input("server ip >> ")
portaServidor = int(input("server port >> "))

if len(ipServidor) == 0:
    ipServidor = '127.0.0.1'

cliente = socket(AF_INET, SOCK_STREAM)

while True:
    try:
        cliente.connect((ipServidor, portaServidor))
        print("Conectado ao Servidor")
        break
    except:
        print("Servidor offline")

while True:
    data = input(">> ")

    cliente.send(data.encode())

    if data == 'exit':
        break

    resp = cliente.recv(2048)
    print("server respond with: ", resp.decode())