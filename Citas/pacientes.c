#include <stdio.h>
#include <string.h>
#include "pacientes.h"


int cedulaExiste(const char *cedula) {
	FILE *archivo = fopen("data/pacientes.txt", "r");
	if (!archivo){
		printf("\nNo existen registros.\n");
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
	while (getchar() != '\n');
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
	int hayPacientes = 0;
	
	printf("\n=== Lista de Pacientes ===\n");
	
	while (fscanf(archivo, "%[^;];%[^;];%d;%[^;];%[^\n]\n",
				  p.nombre, p.cedula, &p.edad,
				  p.telefono, p.correo) == 5) {
		
		hayPacientes = 1;
		
		printf("\nNombre: %s", p.nombre);
		printf("\nCedula: %s", p.cedula);
		printf("\nEdad: %d", p.edad);
		printf("\nTelefono: %s", p.telefono);
		printf("\nCorreo: %s\n", p.correo);
		printf("-----------------------------\n");
	}
	
	if (!hayPacientes) {
		printf("\nNo hay pacientes registrados.\n");
	}
	
	fclose(archivo);
}


int existePaciente(const char *cedulaBuscada){
	FILE *file = fopen("data/pacientes.txt", "r");
	if (!file) return 0;
	
	Paciente p;
	
	while (fscanf(file, "%[^;];%[^;];%d;%[^;];%[^\n]\n",
				  p.nombre, p.cedula, &p.edad,
				  p.telefono, p.correo) == 5) {
		
		if (strcmp(p.cedula, cedulaBuscada) == 0) {
			fclose(file);
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}

	

	
