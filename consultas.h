#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <mariadb/mysql.h>

typedef struct {
} ConexionDB;


/**
 * @brief 
 * @return 
 */
ConexionDB* conexion_bd();

/**
 * @brief 
 * @param 
 */
void cerrar_conexion(ConexionDB *conexion);

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
int insertar_datos(ConexionDB *conexion, const char *nombre, int edad, int matricula, int grado, const char *materia);

#endif
