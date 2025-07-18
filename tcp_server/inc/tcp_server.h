#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

enum operaciones_servidor {

	STATUS_OK,
	STATUS_ERROR,
};

/* Prototipo de funciones ----------------------------------------------------*/
int tcp_server_init(void);
int tcp_new_conn(char * msg, int msg_size);
int tcp_send_msg(char * msg, int msg_size);
int tcp_connection_close(void);

#endif
