#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "../MODULOS_GESTION/gestionBD.h"
#include "servidor.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define TAMAINO_SENDBUFF 1024
#define TAMAINO_RECVBUFF 512
#define BYTES 2

//gcc Servidor/mainServidor.c Servidor/servidor.c sqlite/sqlite3.c -o server.exe -lws2_32


int main(){

    WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[TAMAINO_SENDBUFF], recvBuff[TAMAINO_RECVBUFF];

    printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
	    printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

    printf("Initialised.\n");
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

    if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

    printf("Bind done.\n");


    if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
    }

    printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

    closesocket(conn_socket);

    do {
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if(bytes > 0){
			printf("Code received: %s \n", recvBuff);

			char codigo[3];
			strncpy(codigo, recvBuff, 2);
			codigo[2] = '\0';  // Agregar caracter nulo al final

			if (strcmp(codigo, "00") == 0) {
				break;
			} else if (strcmp(codigo, "01") == 0) {
				Usuario u=strAUsuario(recvBuff);
				registrarUsuario(u);
				strcpy(sendBuff, "1");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			} else if (strcmp(codigo, "02") == 0) {
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
		}
	} while (1);
    closesocket(comm_socket);
	WSACleanup();

	return 0;



}