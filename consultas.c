#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consultas.h"

ConnBD* connbd() {
    ConnBD *con = (ConnBD *) malloc(sizeof(ConnBD));
    if (con == NULL) {
        fprintf(stderr, "Error al asignar memoria para la conexión.\n");
        return NULL;
    }

    con->conn = mysql_init(NULL);
    if (con->conn == NULL) {
        fprintf(stderr, "Error al inicializar MYSQL: %s\n", mysql_error(con->conn));
        free(con);
        return NULL;
    }

    if (mysql_real_connect(con->conn, "localhost", "yael", "12345", "mosquito_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error al conectar a la base de datos: %s\n", mysql_error(con->conn));
        mysql_close(con->conn);
        free(con);
        return NULL;
    }

    printf("Se conecto a la base de datos.\n");
    return con;
}

void cerrar_conexion(ConnBD *con) {
    if (con != NULL) {
        mysql_close(con->conn);
        free(con);
        printf("Conexión cerrada.");
    }
}

int insertar_datos(ConnBD *con, const char *nombre, int edad, int matricula, int grado, const char *materia) {
    if (con == NULL || con->conn == NULL) {
        fprintf(stderr, "Conexión no válida.\n");
        return -1;
    }

    char query[512];
    snprintf(query, sizeof(query),
             "INSERT INTO estudiantes (nombre, edad, matricula, grado, materia) VALUES ('%s', %d, %d, %d, '%s')",
             nombre, edad, matricula, grado, materia);

    if (mysql_query(con->conn, query)) {
        fprintf(stderr, "Error al insertar datos %s\n", mysql_error(con->conn));
        return -1;
    }

    printf("Datos insertados correctamente");
    return 0;
}
