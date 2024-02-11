import socket
import pickle

# Класс, экземпляр которого нужно передать на сервер
class Info:
    x = 5
    y = 10


if __name__ == '__main__':
    # Посылаемый экземпляр класса
    infoObject = Info()
    infoObject.x = 47 # привет Роме Минкину

    # Сериализация
    data = pickle.dumps(infoObject)
    # Сокет для подключения
    _s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    _s.connect(('127.0.0.1', 6000))

    # Ожидание подключения второго клиента к серверу (cpp)
    _s.recv(8)

    # Передача экземпляра
    _s.sendall(data)