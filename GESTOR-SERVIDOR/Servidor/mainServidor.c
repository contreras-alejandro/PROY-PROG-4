#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "../MODULOS_GESTION/gestionBD.h"
#include "gestionCodigos.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define TAMAINO_SENDBUFF 100000
#define TAMAINO_RECVBUFF 100000
#define BYTES 2

//gcc Servidor/mainServidor.c Servidor/gestionCodigos.c sqlite/sqlite3.c MODULOS_GESTION/gestionBD.c MODULOS_GESTION/gestionServer.c -o server.exe -lws2_32


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

			if (strcmp(codigo, "00") == 0) { ////////////////////////////////// Cerrar = 00
				logger(0,"Recibido el codigo 00, CERRAR");
				break;
			} else if (strcmp(codigo, "01") == 0) { /////////////////////////// Registro = 01
			logger(0,"Recibido el codigo 01, REGISTRO");
				Usuario u=strAUsuario(recvBuff);
				registrarUsuario(u);
				strcpy(sendBuff, "1");
				logger(0,"USUARIO REGISTRADO");
				send(comm_socket, sendBuff, strlen(sendBuff), 0);
				
			} else if (strcmp(codigo, "02") == 0) { ////////////////////////// Login = 02
			logger(0,"Recibido codigo 02: Log In");
				Usuario* usr=NULL;
			    char* token = strtok(recvBuff, "$");
				token = strtok(NULL, "$"); // Obtener segundo token (usr)
				char* usuario = token;
				token = strtok(NULL, "$"); // Obtener tercer token (contraseña)
				char* contrasena = token;
				usr = loginUsuario(usuario, contrasena);			
				if (usr != NULL) {
					logger(0,"LOG IN con exito");
					char* strUsr=usuarioAStr(usr);
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, strUsr);
					send(comm_socket, sendBuff, strlen(sendBuff), 0);
					
				} else {
					logger(1,"LOG IN fallido");
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, "0");
					send(comm_socket, sendBuff, strlen(sendBuff), 0);
				}
			}else if (strcmp(codigo, "03") == 0) { //////////////////// Actividades/Fecha = 03
				 //Actividades por fecha
				logger(0,"Recibido el codigo 03, MOSTRAR ACTIVIDADES");
				char* act = malloc(strlen(obtenerActividadesFecha()));
				strcpy(act,obtenerActividadesFecha());
				memset(sendBuff, 0, strlen(sendBuff));				
				strcpy(sendBuff, act);
				logger(0,"Mandando actividades");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}else if (strcmp(codigo, "04") == 0) { ////////////////////// Actividades/Publico = 04
				logger(0,"Recibido el codigo 04, MOSTRAR ACTIVIDADES");
				char* act = malloc(strlen(obtenerActividadesTodas()));
				strcpy(act,obtenerActividadesTodas());
				memset(sendBuff, 0, strlen(sendBuff));				
				strcpy(sendBuff, act);
				logger(0,"Mandando actividades");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}else if (strcmp(codigo, "05") == 0) { /////////////////////// Actividades/Top 10 valoradas = 05
				logger(0,"Recibido el codigo 03, MOSTRAR ACTIVIDADES");
				char* act = malloc(strlen(obtenerActividadesFecha()));
				strcpy(act,obtenerActividadesMejor());
				memset(sendBuff, 0, strlen(sendBuff));				
				strcpy(sendBuff, act);
				logger(0,"Mandando actividades");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}  else if (strcmp(codigo, "06") == 0) { //////////////////// Eliminar inscripción por ID = 06
				char* token = strtok(recvBuff, "$");
				token = strtok(NULL, "$"); // Obtener segundo token (ID de actividad)
				int idActividad = atoi(token); // Convertir a entero utilizando atoi
				token = strtok(NULL, "$"); // Obtener tercer token (ID de usuario)
				int idUsuario = atoi(token); // Convertir a entero utilizando atoi

				char idActStr[100];
				char idUsuStr[100];
				sprintf(idActStr, "%d", idActividad);
				sprintf(idUsuStr, "%d", idUsuario);
				Actividad* act=NULL;
				//EJECUTAMOS SQL OPERACION
				int idAct = atoi(idActStr);
				act = buscarActividadPorId(idAct);

				if(act!=NULL){
					int resultado = eliminarInscripcion(idActStr, idUsuStr); // Llama a la función para eliminar la inscripción
					logger(0,"ACTIVIDAD BUSCADA con exito");
					char* strAct=actividadAStr(act);
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, strAct);
					send(comm_socket, sendBuff, strlen(sendBuff), 0);
					recv(comm_socket,recvBuff,512,0);
					if (recvBuff[0] == '1')
					{
						if (resultado=1)
						{
							logger(0,"Inscripcion eliminada con exito");
							printf("Mando un 1");
							memset(sendBuff, 0, strlen(sendBuff)); 
							strcpy(sendBuff, "1");
							send(comm_socket, sendBuff, strlen(sendBuff), 0);
							
						}else{
							logger(1,"No se pudo eliminar la inscrpcion");
							printf("Mando un 0");
							memset(sendBuff, 0, strlen(sendBuff)); 
							strcpy(sendBuff, "0");
							send(comm_socket, sendBuff, strlen(sendBuff), 0);

						}
						
					}else
					{
						logger(0,"Se cancelo la des-inscripcion");
						printf("Mando un 0");
						memset(sendBuff, 0, strlen(sendBuff)); 
						strcpy(sendBuff, "0");
						send(comm_socket, sendBuff, strlen(sendBuff), 0);
						
					}
					

				}else{
					
					printf("Mando un 0");
					logger(1,"LOG IN fallido");
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, "0");
					send(comm_socket, sendBuff, strlen(sendBuff), 0);

				}

			}else if (strcmp(codigo, "07") == 0) { /////////////////////////  Inscripción por ID = 07
				char* token = strtok(recvBuff, "$");
				token = strtok(NULL, "$"); // Obtener segundo token (ID de actividad)
				int idActividad = atoi(token); // Convertir a entero utilizando atoi
				token = strtok(NULL, "$"); // Obtener tercer token (ID de usuario)
				int idUsuario = atoi(token); // Convertir a entero utilizando atoi

				char idActStr[150];
				char idUsuStr[150];
				sprintf(idActStr, "%d", idActividad);
				sprintf(idUsuStr, "%d", idUsuario);
				Actividad* act=NULL;
				//EJECUTAMOS SQL OPERACION
				int idAct = atoi(idActStr);
				act = buscarActividadPorId(idAct);

				if(act!=NULL){
					logger(0,"ACTIVIDAD BUSCADA con exito");
					char* strAct=actividadAStr(act);
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, strAct);
					send(comm_socket, sendBuff, strlen(sendBuff), 0);
					recv(comm_socket,recvBuff,512,0);
					if (recvBuff[0] == '1')
					{
						int resultado = insertarInscrSipcionActividad(idActStr, idUsuStr); // Llama a la función para eliminar la inscripción
						if (resultado=1)
						{
							logger(0,"Inscripcion anadida con exito");
							printf("Mando un 1");
							memset(sendBuff, 0, strlen(sendBuff)); 
							strcpy(sendBuff, "1");
							send(comm_socket, sendBuff, strlen(sendBuff), 0);
							
						}else{
							logger(1,"No se pudo realizar la inscrpcion");
							printf("Mando un 0");
							memset(sendBuff, 0, strlen(sendBuff)); 
							strcpy(sendBuff, "0");
							send(comm_socket, sendBuff, strlen(sendBuff), 0);

						}
						
					}else
					{
						logger(0,"Se cancelo la inscripcion");
						printf("Mando un 0");
						memset(sendBuff, 0, strlen(sendBuff)); 
						strcpy(sendBuff, "0");
						send(comm_socket, sendBuff, strlen(sendBuff), 0);
						
					}
					

				}else{
					
					printf("Mando un 0");
					logger(1,"LOG IN fallido");
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, "0");
					send(comm_socket, sendBuff, strlen(sendBuff), 0);

				}
			}else if (strcmp(codigo, "09") == 0) { /////////////////////////////  Valorar ACTIVIDAD por ID 0 09
				char* token = strtok(recvBuff, "$");
				token = strtok(NULL, "$"); // Obtener segundo token (ID de actividad)
				int idActividad = atoi(token); // Convertir a entero utilizando atoi
				token = strtok(NULL, "$"); // Obtener tercer token (ID de usuario)
				int idUsuario = atoi(token); // Convertir a entero utilizando atoi

				char idActStr[150];
				char idUsuStr[150];
				char nota[150];
				sprintf(idActStr, "%d", idActividad);
				sprintf(idUsuStr, "%d", idUsuario);



				Actividad* act=NULL;
				//EJECUTAMOS SQL OPERACION
				act = buscarActividadPorId(idActividad);
				if(act!=NULL){
					logger(0,"ACTIVIDAD BUSCADA con exito");
					char* strAct=actividadAStr(act);
					
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, strAct);
					send(comm_socket, sendBuff, strlen(sendBuff), 0);
					recv(comm_socket,recvBuff,512,0);
					if (recvBuff[0] == '1')
					{
						token = strtok(recvBuff, "$");
						token = strtok(NULL, "$");
						char * nt = token;

						 double valoracionDouble = strtod(nt, NULL);


						int comprobacion = comprobarInscripcionValorar(idActStr, idUsuStr);
						
						if (comprobacion==1)
						{
							int resultado = insertarValoracionActividad(idActStr, idUsuStr,valoracionDouble);
							if(resultado==1){
							logger(0,"Valoracion anadida con exito");
							printf("Mando un 1");
							memset(sendBuff, 0, strlen(sendBuff)); 
							strcpy(sendBuff, "1");
							send(comm_socket, sendBuff, strlen(sendBuff), 0);

							}
							
						}else{
							logger(0,"No se pudo realizar la valoracion, no inscrito en esa actividad");
							printf("Mando un 0");
							memset(sendBuff, 0, strlen(sendBuff)); 
							strcpy(sendBuff, "0");
							send(comm_socket, sendBuff, strlen(sendBuff), 0);

						}
						
					}
					else{
						//NO QUIERE VALORARLA!
						
					}


				}
				else{
					
					printf("Mando un 0");
					logger(1,"LOG IN fallido");
					memset(sendBuff, 0, strlen(sendBuff)); 
					strcpy(sendBuff, "0");
					send(comm_socket, sendBuff, strlen(sendBuff), 0);
				}

			}else if (strcmp(codigo, "10") == 0) { ////////////////////// Ver inscripciones = 10
				char* token = strtok(recvBuff, "$");
				token = strtok(NULL, "$"); // Obtener segundo token
				int idUsr = atoi(token);

				char idUsrStr[100];
				sprintf(idUsrStr, "%d", idUsr);


				logger(0,"Recibido el codigo 10, MOSTRAR INSCRIPCIONES DE UN USUARIO");
				char* ins = malloc(strlen(obtenerInscripciones(idUsrStr)));
				strcpy(ins,obtenerInscripciones(idUsrStr));
				memset(sendBuff, 0, strlen(sendBuff));				
				strcpy(sendBuff, ins);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
		}
	} while (1);
    closesocket(comm_socket);
	WSACleanup();

	return 0;



}