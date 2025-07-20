#ifndef DISCO_H_
#define DISCO_H_

enum operaciones_disco {

	O_ERROR = -3,
	ARCHIVO_EXISTE,
	ARCHIVO_NO_EXISTE,
	O_OK,
};

/* Prototipo de funciones ----------------------------------------------------*/
int almacenar_elemento(char * clave, char * valor);
int recuperar_elemento(char * clave, char * valor);
int borrar_elemento(char * clave);

#endif /* DISCO_H_ */
