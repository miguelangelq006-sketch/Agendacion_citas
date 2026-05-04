#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "autenticacion.h"
#include "validaciones.h"

#define ARCHIVO_CUENTAS "data/cuentas.txt"



char rolActual[15];
char usuarioActual[30];

// ------------------------------------------------
// LOGIN CON ROLES
// ------------------------------------------------
int login(int *codigoMedico, char cedulaPaciente[], int tamCedula) {
	
	FILE *file = fopen("data/cuentas.txt", "r");
	if (!file) {
		printf("Error: No existe el archivo de cuentas.\n");
		return 0;
	}
	
	char usuario[30], contrasena[30];
	char u[30], c[30], rol[15];
	int intentos = 3;
	
	while (intentos > 0) {
		
		printf("Usuario: ");
		leerCadena(usuario, sizeof(usuario));
		
		printf("Contrasena: ");
		leerCadena(contrasena, sizeof(contrasena));

		rewind(file);
		
		while (fscanf(file, "%[^;];%[^;];%s\n", u, c, rol) == 3) {
			
			if (strcmp(usuario, u) == 0 && strcmp(contrasena, c) == 0) {
				
				fclose(file);
				
				if (strcmp(rol, "ADMIN") == 0) {
					return 1; // ADMIN
				}
				
				if (strcmp(rol, "MEDICO") == 0) {
					printf("Codigo del medico: ");
					*codigoMedico = leerEnteroPositivo();
					return 2; // MEDICO
				}
				
				if (strcmp(rol, "PACIENTE") == 0) {
					leerCadenaSoloNumeros("Cedula del paciente: ",cedulaPaciente, tamCedula);
					while(getchar() != '\n');
					return 3; // PACIENTE
				}
			}
		}
		
		intentos--;
		printf("Credenciales incorrectas. Intentos restantes: %d\n", intentos);
	}
	
	fclose(file);
	return 0;
}


// ------------------------------------------------
// CREAR USUARIO (ADMIN)
// ------------------------------------------------
void crearUsuario() {
	FILE *file = fopen(ARCHIVO_CUENTAS, "a");
	if (!file) {
		printf("Error al abrir archivo de cuentas.\n");
		return;
	}
	
	char usuario[30], contrasena[30];
	int rol;
	
	printf("Nuevo usuario: ");
	scanf("%s", usuario);
	printf("Contrasena: ");
	scanf("%s", contrasena);
	
	printf("Rol:\n");
	printf("1. ADMIN\n");
	printf("2. MEDICO\n");
	printf("3. PACIENTE\n");
	printf("Seleccione: ");
	rol = leerEnteroPositivo();
	
	switch (rol) {
	case 1:
		fprintf(file, "%s;%s;ADMIN\n", usuario, contrasena);
		break;
	case 2:
		fprintf(file, "%s;%s;MEDICO\n", usuario, contrasena);
		break;
	case 3:
		fprintf(file, "%s;%s;PACIENTE\n", usuario, contrasena);
		break;
	default:
		printf("Rol invalido.\n");
		fclose(file);
		return;
	}
	
	fclose(file);
	printf("Usuario creado correctamente.\n");
}



// ------------------------------------------------
// LISTAR USUARIOS (ADMIN)
// ------------------------------------------------
void listarUsuarios() {
	FILE *file = fopen(ARCHIVO_CUENTAS, "r");
	if (!file) {
		printf("No existe el archivo de cuentas.\n");
		return;
	}
	
	char u[30], c[30], r[15];
	printf("\n--- LISTA DE USUARIOS ---\n");
	
	while (fscanf(file, "%[^;];%[^;];%s\n", u, c, r) != EOF) {
		printf("Usuario: %s | Rol: %s\n", u, r);
	}
	
	fclose(file);
}
