/**
******************************************************************************
 * @file    tcp_server.c
 * @author  Lcdo. Mariano Ariel Deville
 * @date    18/07/2025
 * @brief   Trabajo práctico para la materia Sistemas Operativos de Propósito
 * 			General
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../inc/tcp_server.h"

/* Definiciones --------------------------------------------------------------*/
#define PORT 			5000
#define IP_INTERFACE	"127.0.0.1"

/* Variables privadas --------------------------------------------------------*/
static int soket_fd, conn_fd;

/**
 * @brief  Inicializo un servidor TCP
 * @param  None.
  * @retval Estado de la operación.
 */
int tcp_server_init(void) {

	printf("Inicializando servidor TCP.\n");
	soket_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, IP_INTERFACE, &(serveraddr.sin_addr)) <= 0) {

		fprintf(stderr, "ERROR invalid server IP.\n");
		return STATUS_ERROR;
	}

	if(bind(soket_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {

		perror("bind");
		return STATUS_ERROR;
	}

	if(listen(soket_fd, 1) == -1) {

		perror("listen");
		return STATUS_ERROR;
	}
	return STATUS_OK;
}

/**
 * @brief  Función bloqueante que espera una conección desde un cliente
 * 			y un mensaje del cliente,
 * @param  Puntero al buffer de entrada.
 * @param  Entero con el tamaño del buffer.
 * @retval Estado de la operación.
 */
int tcp_new_conn(char *msg, int msg_size) {

	socklen_t addr_len = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	printf("\nserver: esperando una conexion...\n");

	if((conn_fd = accept(soket_fd, (struct sockaddr *)&clientaddr, &addr_len)) == -1) {

		perror("accept");
		return STATUS_ERROR;
	}

	char ipClient[32];
	inet_ntop(AF_INET, &(clientaddr.sin_addr), ipClient, sizeof(ipClient));
	printf("server: conexion desde:  %s\n", ipClient);
	int read_size = read(conn_fd, msg, msg_size);

	if(read_size == -1) {

		perror("read");
		return STATUS_ERROR;
	}
	msg[read_size] = 0x00;
	printf("server: recibi %d bytes:%s", read_size, msg);
	return STATUS_OK;
}

/**
 * @brief  Función que envía un mensaje al cliente conectado
 * @param  Puntero al mensaje de salida.
 * @param  Entero con el tamaño del mensaje.
 * @retval Estado de la operación.
 */
int tcp_send_msg(char * msg, int msg_size){

	int n = write(conn_fd, msg, msg_size);

	if(n == -1) {

		perror("write");
		return STATUS_ERROR;
	}
	printf("server: envie %d bytes.\n", n);
	return STATUS_OK;
}

/**
 * @brief  Función que cierra un conección.
 * @param  None.
 * @retval Estado de la operación.
 */
int tcp_connection_close(void) {

	if(close(conn_fd) == -1) {

		perror("close");
		return STATUS_ERROR;
	}
	return STATUS_OK;
}

