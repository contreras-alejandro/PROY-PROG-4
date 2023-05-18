#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "../Menu/menu.h"
#include <vector>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

//g++ Menu/menu.cpp Cliente/mainCliente.cpp Clases/Usuario.cpp Clases/Actividad.cpp Menu/gestionLog.cpp -o cliente.exe -lws2_32

int main(){
    WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[100000], recvBuff[100000];

    printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

    printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

    printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);


    if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

    char opcion;

    system("cls");
    menuInicio(s, sendBuff, recvBuff);
	closesocket(s);
	WSACleanup();

    return 0;



}
