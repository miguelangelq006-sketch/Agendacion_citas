#ifndef AUTENTICACION_H
#define AUTENTICACION_H

// Login
int login(int *codigoMedico, char cedulaPaciente[]);

// Funciones solo para ADMIN
void crearUsuario();
void eliminarUsuario();
void listarUsuarios();

#endif

