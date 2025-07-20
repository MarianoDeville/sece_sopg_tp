/**
******************************************************************************
 * @file    disco.c
 * @author  Lcdo. Mariano Ariel Deville
 * @date    18/07/2025
 * @brief   Trabajo práctico para la materia Sistemas Operativos de Propósito
 * 			General
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/disco.h"

/**
 * @brief  Creo un archivo en disco,
 * @param  Puntero al string con el nombre del archivo.
 * @param  Puntero al string con el contenido a guardar.
 * @retval Estado de la operación.
 * @note   Si el archivo existe se sobreescribirá el contenido.
 */
int almacenar_elemento(char * clave, char * valor) {

	FILE *archivo = fopen(clave, "w");

	if(archivo == NULL) {

		perror("file write");
		return O_ERROR;
	}
	fprintf(archivo, "%s", valor);
	fclose(archivo);
	return O_OK;
}

/**
 * @brief  Leo un archivo en disco,
 * @param  Puntero al string con el nombre del archivo.
 * @param  Puntero al string donde guardar lo recuperaro.
 * @retval Estado de la operación, si es exitosa se devuelve
 * 			la cantidad de bytes leídos.
 */
int recuperar_elemento(char * clave, char * valor) {

	if(access(clave, F_OK) != 0)
		return ARCHIVO_NO_EXISTE;
	FILE *archivo = fopen(clave, "r");

	if (archivo == NULL) {

		perror("file read");
		return O_ERROR;
	}
	int pos = 0;
	while ((valor[pos++] = fgetc(archivo)) != EOF);
	valor[pos -1] = 0X00;
	fclose(archivo);
	return pos;
}

/**
 * @brief  Elimino un archivo en disco,
 * @param  Puntero al string con el nombre del archivo.
 * @retval Estado de la operación.
 */
int borrar_elemento(char * clave) {

	if(access(clave, F_OK) != 0)
		return ARCHIVO_NO_EXISTE;

	if (remove(clave) != 0) {

		perror("file delete");
		return O_ERROR;
	}
	return O_OK;
}
