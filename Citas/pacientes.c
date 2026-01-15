#include <stdio.h>
#include <string.h>
#include "paciente.h"


int cedulaExiste(const char *cedula) {
	FILE *archivo = fopen("data/pacientes.txt", "r");
	if (!archivo){
		printf("\nERROR: No se pudo abrir el archivo.\n");
		return 0;
	}
	
	Paciente p;
	
	while (fscanf(archivo, "%[^;];%[^;];%d;%[^;];%[^\n]\n",
				  p.nombre, p.cedula, &p.edad, p.telefono, p.correo) == 5) {
		if (strcmp(p.cedula, cedula) == 0) {
			fclose(archivo);
			return 1;
		}
	}
	
	fclose(archivo);
	return 0;
}

void registrarPaciente() {
	Paciente p;
	
	printf("\n=== Registro de Paciente ===\n");
	
	printf("Nombre: ");
	fflush(stdin);
	fgets(p.nombre, 50, stdin);
	p.nombre[strcspn(p.nombre, "\n")] = 0;
	
	printf("Cedula: ");
	scanf("%s", p.cedula);
	
	// Validar cédula duplicada
	if (cedulaExiste(p.cedula)) {
		printf("\nERROR: Esta cédula ya está registrada.\n");
		return;
	}
	
	printf("Edad: ");
	scanf("%d", &p.edad);
	
	printf("Telefono: ");
	scanf("%s", p.telefono);
	
	printf("Correo: ");
	scanf("%s", p.correo);
	
	// Guardar en archivo
	FILE *archivo = fopen("data/pacientes.txt", "a");
	if (!archivo) {
		printf("\nERROR: No se pudo abrir el archivo.\n");
		return;
	}
	
	fprintf(archivo, "%s;%s;%d;%s;%s\n",
			p.nombre, p.cedula, p.edad, p.telefono, p.correo);
	
	fclose(archivo);
	
	printf("\nPaciente registrado correctamente.\n");
}

void listarPacientes() {
	FILE *archivo = fopen("data/pacientes.txt", "r");
	if (!archivo) {
		printf("\nNo hay pacientes registrados.\n");
		return;
	}
	
	Paciente p;
	
	printf("\n=== Lista de Pacientes ===\n");
	
	while (fscanf(archivo, "%[^;];%[^;];%d;%[^;];%[^\n]\n",
				  p.nombre, p.cedula, &p.edad, p.telefono, p.correo) == 5) {
		
		printf("\nNombre: %s", p.nombre);
		printf("\nCedula: %s", p.cedula);
		printf("\nEdad: %d", p.edad);
		printf("\nTelefono: %s", p.telefono);
		printf("\nCorreo: %s\n", p.correo);
		printf("-----------------------------\n");
	}
	
	fclose(archivo);
}
int existePaciente(char cedulaBuscada[]) {
	FILE *file = fopen("data/pacientes.txt", "r");
	if (!file) return 0;
	
	char cedula[15], nombre[50], telefono[15];
	int edad;
	
	while (fscanf(file, "%[^;];%[^;];%d;%s\n",
				  cedula, nombre, &edad, telefono) != EOF) {
		if (strcmp(cedula, cedulaBuscada) == 0) {
			fclose(file);
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}
