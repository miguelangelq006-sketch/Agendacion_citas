#ifndef AUTENTICACION_H
#define AUTENTICACION_H
#define TAM_CEDULA 10

// Login
int login(int *codigoMedico, char cedulaPaciente[], int tamCedula);

// Funciones solo para ADMIN
void crearUsuario();
void eliminarUsuario();
void listarUsuarios();

#endif

