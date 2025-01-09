#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <mariadb/mysql.h>

typedef struct {
} ConnBD


/**
 * @brief 
 * @return 
 */
ConnBD* connbd();

/**
 * @brief 
 * @param 
 */
void cerrar_conexion(ConnBD *conexion);

/**
 * @brief 
 * @param conexion 
 * @param nombre 
 * @param edad 
 * @param matricula 
 * @param grado
 * @param materia 
 * @return 
 */
int insertar_datos(ConnBD *conexion, const char *nombre, int edad, int matricula, int grado, const char *materia);

#endif
