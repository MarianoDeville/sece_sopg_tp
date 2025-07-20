#!/bin/bash

gcc main.c tcp_server.c disco.c -o servidor_tcp -Wall -Wextra -Werror

if [ $? -eq 0 ]; then
    echo "Compilación exitosa."
else
    echo "Error en la compilación."
fi
