#ifndef AUTENTICACION_H
#define AUTENTICACION_H

// Rol del usuario que inició sesión
extern char rolActual[15];
extern char usuarioActual[30];

// Login
int login();

// Funciones solo para ADMIN
void crearUsuario();
void eliminarUsuario();
void listarUsuarios();

#endif

