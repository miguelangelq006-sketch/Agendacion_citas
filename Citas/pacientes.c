#include <stdio.h>
#include <string.h>
#include "pacientes.h"
#include "validaciones.h"


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
	
	// -------------------------
	// NOMBRE
	// -------------------------
	do {
		printf("Nombre del paciente: ");
	} while (!leerSoloLetras(p.nombre, sizeof(p.nombre)));
	
	// -------------------------
	// CÉDULA
	// -------------------------
	while (1) {
		leerCadenaSoloNumeros("Cedula (10 digitos): ", p.cedula, sizeof(p.cedula));
		
		if (strlen(p.cedula) != 10) {
			printf("ERROR: La cedula debe tener 10 digitos.\n");
			continue;
		}
		
		if (cedulaExiste(p.cedula)) {
			printf("ERROR: Esta cedula ya esta registrada.\n");
			continue;
		}
		
		while(getchar() != '\n');
		break;
	}
	
	// -------------------------
	// EDAD
	// -------------------------
	while (1) {
		printf("Edad: ");
		p.edad = leerEnteroPositivo();
		
		if (p.edad < 0 || p.edad > 120) {
			printf("ERROR: Edad invalida. Ingrese un valor entre 1 y 120.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// TELÉFONO
	// -------------------------
	while (1) {
		leerCadenaSoloNumeros("Telefono (10 digitos): ", p.telefono, sizeof(p.telefono));
		
		if (strlen(p.telefono) != 10) {
			printf("ERROR: Telefono invalido.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// CORREO
	// -------------------------
	while (1) {
		printf("Correo: ");
		leerCadena(p.correo, sizeof(p.correo));
		
		if (strchr(p.correo, '@') == NULL || strchr(p.correo, '.') == NULL) {
			printf("ERROR: Correo invalido.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// GUARDAR
	// -------------------------
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

	

	
