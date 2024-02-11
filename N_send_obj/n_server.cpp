#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include <ctime>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")



#define MAX_POOL_SIZE 10
#define NUM_OF_CLIENTS 2

SOCKET CONNECTIONS[NUM_OF_CLIENTS];

int main(int argc, char* argv[]) {
    // инициализация случайных значений
    srand(time(NULL));
    // Инициализация и загрузка библиотеки сокетов
    WSADATA wsaData;
    // Версия библиотеки Winsock
    WORD DLLVersion = MAKEWORD(2, 1);
    int rc = WSAStartup(DLLVersion, &wsaData);

    if (rc != 0) {
        fprintf(stderr, "Error during socket's initializing\n");
        return 1;
    }

    // Информация о нашем сокете
    // Инициализация параметров соединения для сокета
    SOCKADDR_IN sockParams;
    int sockParamsSize = sizeof(sockParams);
    sockParams.sin_addr.s_addr = htonl(INADDR_ANY);
    sockParams.sin_family = AF_INET;
    sockParams.sin_port = htons(6000);

    // Создание сокета
    SOCKET sockListen;
    sockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockListen == INVALID_SOCKET) { // INVALID_SOCKET == 0
        fprintf(stderr, "Error during socket's creating\n");
        return 1;
    }

    // Привязка сокета
    if (bind(sockListen, (SOCKADDR*)&sockParams, sockParamsSize) == SOCKET_ERROR) {
        printf("Bind failed...\n");
    };
    // Прослушивание
    if (listen(sockListen, MAX_POOL_SIZE) == SOCKET_ERROR) {
        printf("Listen failed...\n");
    };


    // Сокет для удерживания соединения с клиентом
    SOCKET holdConnectionSock;

    // Два клиента

    // Установка подключений для двух клиентов
    for (int i = 0; i < NUM_OF_CLIENTS; i++)
    {
        holdConnectionSock = accept(sockListen, (SOCKADDR*)&sockParams, &sockParamsSize);

        if (holdConnectionSock == INVALID_SOCKET)
            printf("Error!\n");
        else {
            printf("Success!\n");
            CONNECTIONS[i] = holdConnectionSock;
        }
    }
    
    // Сокеты подключений для клиентов
    SOCKET first = CONNECTIONS[0], second = CONNECTIONS[1];
    int bytesRead;
    // Декоративная передача сообщения первому клиенту
    // нужна, чтобы клиент 1 не передавал сообщение раньше,
    // чем подключится клиент 2
    char y = 1;
    bytesRead = send(first, (const char*)&y, sizeof(char), 0);
    
    // Получение сообщения от клиента 1
    char* x[45];
    bytesRead = recv(first, (char*)&x, 45,0);
    // Отправка сообщения клиенту 2
    bytesRead = send(second, (const char*)&x, 45, 0);


    getchar();
    return 0;
}