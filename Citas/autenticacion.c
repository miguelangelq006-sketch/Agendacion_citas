#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "autenticacion.h"

#define ARCHIVO_CUENTAS "data/cuentas.txt"

char rolActual[15];
char usuarioActual[30];

// ------------------------------------------------
// LOGIN CON ROLES
// ------------------------------------------------
int login() {
	
	FILE *file = fopen(ARCHIVO_CUENTAS, "r");
	if (!file) {
		printf("Error: No existe el archivo de cuentas.\n");
		return 0;
	}
	
	char usuario[30], contrasena[30];
	char u[30], c[30], r[15];
	int encontrado = 0;
	int intentos = 3;
	do{
		printf("Usuario: ");
		scanf("%s", usuario);
		printf("Contrasena: ");
		scanf("%s", contrasena);
		
		while (fscanf(file, "%[^;];%[^;];%s\n", u, c, r) != EOF) {
			if (strcmp(usuario, u) == 0 && strcmp(contrasena, c) == 0) {
				encontrado = 1;
				strcpy(rolActual, r);
				strcpy(usuarioActual, u);
				break;
			}
		}
		
		fclose(file);
		
		if (encontrado) {
			printf("\nBienvenido %s (%s)\n", usuarioActual, rolActual);
			return 1;
		} else {
			printf("\nCredenciales incorrectas.\n");
			printf("Intentos restantes: %d.\n", intentos-1);
			intentos--;
		}
	} while(intentos != 0);
	
	if(intentos == 0){
		printf("Maximo de intentos alcanzados.\n");
		return 0;
	}
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
	scanf("%d", &rol);
	
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
// ELIMINAR USUARIO (ADMIN)
// ------------------------------------------------
void eliminarUsuario() {
	FILE *file = fopen(ARCHIVO_CUENTAS, "r");
	FILE *temp = fopen("data/temp.txt", "w");
	
	if (!file || !temp) {
		printf("Error al abrir archivos.\n");
		return;
	}
	
	char usuarioEliminar[30];
	char u[30], c[30], r[15];
	int eliminado = 0;
	
	printf("Usuario a eliminar: ");
	scanf("%s", usuarioEliminar);
	
	while (fscanf(file, "%[^;];%[^;];%s\n", u, c, r) != EOF) {
		if (strcmp(u, usuarioEliminar) != 0) {
			fprintf(temp, "%s;%s;%s\n", u, c, r);
		} else {
			eliminado = 1;
		}
	}
	
	fclose(file);
	fclose(temp);
	
	remove(ARCHIVO_CUENTAS);
	rename("data/temp.txt", ARCHIVO_CUENTAS);
	
	if (eliminado)
		printf("Usuario eliminado correctamente.\n");
	else
		printf("Usuario no encontrado.\n");
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
