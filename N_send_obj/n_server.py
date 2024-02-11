""" Передача экземпляра класса на сервер. 
Сериализованный на клиенте (файл n_client1.py) 
передается на сервер и затем восстанавливается."""

import socket,pickle

class Info:
    x = 5
    y = 10


if __name__ == '__main__':

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('127.0.0.1', 6000))
    server.listen(2)
    conn, addr = server.accept()


    a = "Декоративное сообщение"
    conn.sendall(a.encode())
    

    data = None
    while(data is None):
        try:
            data = conn.recv(45)
        except:
            pass
    data = pickle.loads(data)
    print(data.x)