#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "consultas.h"

#define MSG_SIZE 512
#define QUEUE_KEY 1234

struct mensaje {
    long tipo;
    char texto[MSG_SIZE];
};

void procesar_mensaje(const char *msj) {
    char nombre[50], materia[50];
    int edad, matricula, grado;

    if (sscanf(msj, "Nombre: %49[^,], Edad: %d, Matricula: %d, Grado: %d, Materia: %49s",
               nombre, &edad, &matricula, &grado, materia) != 5) {
        fprintf(stderr, "Error: Formato de mensaje incorrecto: %s\n", msj);
        return;
    }

    printf("Datos recibidos correctamente:\n");
    printf("Nombre: %s\n", nombre);
    printf("Edad: %d\n", edad);
    printf("Matricula: %d\n", matricula);
    printf("Grado: %d\n", grado);
    printf("Materia: %s\n", materia);

    ConnBD *conexion = connbd();
    if (conexion == NULL) {
        fprintf(stderr, "Error al conectar con la base de datos.\n");
        return;
    }

    // Insertar datos en la base de datos
    if (insertar_datos(conexion, nombre, edad, matricula, grado, materia) != 0) {
        fprintf(stderr, "Error al insertar datos en la base de datos.\n");
    } else {
        printf("Datos insertados correctamente en la base de datos.\n");
    }

    
}

int main() {
    key_t clave = QUEUE_KEY;
    int msqid;
    struct mensaje msg;

    msqid = msgget(clave, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("Error al crear la cola de mensajes");
        exit(1);
    }

    printf("Servidor iniciado. Esperando mensajes...\n");

    while (1) {
        if (msgrcv(msqid, &msg, MSG_SIZE, 0, 0) == -1) {
            perror("Error al recibir mensaje");
            exit(1);
        }

        if (strcmp(msg.texto, "salir") == 0) {
            printf("Servidor finalizado.\n");
            break; 
        }

        printf("Mensaje recibido: %s\n", msg.texto);

        procesar_mensaje(msg.texto);
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("Error al eliminar la cola de mensajes");
        exit(1);
    }

    return 0;
}

