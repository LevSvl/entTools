import socket
import pickle

# Класс, экземпляр которого нужно получить с сервера
class Info:
    x = 5
    y = 10


if __name__ == '__main__':
    # Сокет для подключения
    _s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Подключение
    _s.connect(('127.0.0.1', 6000))
    
    # Получение сообщения
    data = None
    while(data is None):
        try:
            data = _s.recv(45) #  Размер сериализованного объекта - 45 байт
        except:
            pass

    # Восстановление полученного потока байт в объект класса Info
    recievedData = pickle.loads(data)
    # Убедимся, попробуем получить доступ к атрибуту класса
    print(recievedData.x)


    """Альтернатива строкам 15-20 с порционным получением сообщения"""
    # data = bytes()
    # while len(data) < 35:
    #     chunk = _s.recv(35 - len(data))
    #     if not chunk:
    #         break
    #     data += chunk