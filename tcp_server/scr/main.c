/**
******************************************************************************
 * @file    main.c
 * @author  Lcdo. Mariano Ariel Deville
 * @date    18/07/2025
 * @brief   Trabajo práctico para la materia Sistemas Operativos de Propósito
 * 			General
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/tcp_server.h"
#include "../inc/disco.h"

/* Prototipo de funciones privadas -------------------------------------------*/
static void proceso_msg(char * msg, int msg_size);

int main(void) {

	printf("Trabajo práctico de Sistemas Operativos de propósito General\n");

	if(tcp_server_init() != STATUS_OK) {

		printf("Error crítico.");
		return EXIT_FAILURE;
	}
	char msg_entrada[128];

	while(1) {

		if(tcp_new_conn(msg_entrada, 128) == STATUS_OK) {

			proceso_msg(msg_entrada, strlen(msg_entrada));
		} else {

			fprintf(stderr, "Error inesperado.\n");
			return EXIT_FAILURE;
		}
		tcp_connection_close();
	}
	return EXIT_SUCCESS;
}

/**
 * @brief  Función privada que procesa el mensaje recibido por el puerto TCP y
 * 			actua en consecuencia.
 * @param  Puntero al mensaje recibido.
 * @param  Entero con el tamaño del mensaje.
 * @retval None.
 */
static void proceso_msg(char * msg, int msg_size) {

	if(msg_size < 1) {

		printf("no hay mensaje de entrada\n");
		return;
	}

	if(msg[msg_size - 1] == '\n')
		msg[msg_size - 1] = 0x00;
	char *palabras[5];
	int cant_palabras = 0;
	char *palabra = strtok(msg, " ");

	while (palabra != NULL && cant_palabras < 5) {

		palabras[cant_palabras++] = palabra;
		palabra = strtok(NULL, " ");
	}

	if(!strcmp(palabras[0], "SET")) {

		if(cant_palabras > 2) {

			switch(almacenar_elemento(palabras[1], palabras[2])){

			case O_OK:
				tcp_send_msg("OK", 3);
				break;
			case ARCHIVO_EXISTE:
				tcp_send_msg("DUPLICATE ENTRY", 19);
				break;
			default:
				tcp_send_msg("SYSTEM ERROR", 13);
			}
		} else {

			tcp_send_msg("MUST BE: SET <clave> <valor>", 29);
		}
	} else if(!strcmp(palabras[0], "GET")) {

		if(cant_palabras > 1) {

			char valor_leido[64];
			int long_msg = recuperar_elemento(palabras[1], valor_leido);

			switch(long_msg) {

				case ARCHIVO_NO_EXISTE:
					tcp_send_msg("NOTFOUND", 9);
					break;
				case O_ERROR:
					tcp_send_msg("SYSTEM ERROR", 13);
					break;
				default:
					tcp_send_msg("OK\n", 4);
					tcp_send_msg(valor_leido, long_msg);
			}
		} else {

			tcp_send_msg("MUST BE: GET <clave>", 21);
		}
	} else if(!strcmp(palabras[0], "DEL")) {

		if(cant_palabras > 1) {

			switch(borrar_elemento(palabras[1]) ) {

				case O_OK:
					tcp_send_msg("OK", 3);
					break;
				case ARCHIVO_NO_EXISTE:
					tcp_send_msg("NOTFOUND", 9);
					break;
				default:
					tcp_send_msg("SYSTEM ERROR", 13);
			}
		} else {

			tcp_send_msg("MUST BE: DEL <clave>", 21);
		}
	} else {

		tcp_send_msg("COMMAND NOT FOUND", 18);
	}
}

