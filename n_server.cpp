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
    // ������������� ��������� ��������
    srand(time(NULL));
    // ������������� � �������� ���������� �������
    WSADATA wsaData;
    // ������ ���������� Winsock
    WORD DLLVersion = MAKEWORD(2, 1);
    int rc = WSAStartup(DLLVersion, &wsaData);

    if (rc != 0) {
        fprintf(stderr, "Error during socket's initializing\n");
        return 1;
    }

    // ���������� � ����� ������
    // ������������� ���������� ���������� ��� ������
    SOCKADDR_IN sockParams;
    int sockParamsSize = sizeof(sockParams);
    sockParams.sin_addr.s_addr = htonl(INADDR_ANY);
    sockParams.sin_family = AF_INET;
    sockParams.sin_port = htons(6000);

    // �������� ������
    SOCKET sockListen;
    sockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockListen == INVALID_SOCKET) { // INVALID_SOCKET == 0
        fprintf(stderr, "Error during socket's creating\n");
        return 1;
    }

    // �������� ������
    if (bind(sockListen, (SOCKADDR*)&sockParams, sockParamsSize) == SOCKET_ERROR) {
        printf("Bind failed...\n");
    };
    // �������������
    if (listen(sockListen, MAX_POOL_SIZE) == SOCKET_ERROR) {
        printf("Listen failed...\n");
    };


    // ����� ��� ����������� ���������� � ��������
    SOCKET holdConnectionSock;

    // ��� �������

    // ��������� ����������� ��� ���� ��������
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
    
    // ������ ����������� ��� ��������
    SOCKET first = CONNECTIONS[0], second = CONNECTIONS[1];
    int bytesRead;
    // ������������ �������� ��������� ������� �������
    // �����, ����� ������ 1 �� ��������� ��������� ������,
    // ��� ����������� ������ 2
    char y = 1;
    bytesRead = send(first, (const char*)&y, sizeof(char), 0);
    
    // ��������� ��������� �� ������� 1
    char* x[45];
    bytesRead = recv(first, (char*)&x, 45,0);
    // �������� ��������� ������� 2
    bytesRead = send(second, (const char*)&x, 45, 0);


    getchar();
    return 0;
}