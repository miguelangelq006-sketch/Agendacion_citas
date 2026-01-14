#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "citas.h"

#define ARCHIVO_CITAS "data/citas.txt"
#define ARCHIVO_SEGUIMIENTO "data/seguimiento_citas.txt"


// Verificar si el medico ya tiene cita en fecha/hora
int citaOcupada(int codigoMedico, char fecha[], char hora[]) {
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	if (!file) return 0;
	
	char linea[256];
	while (fgets(linea, sizeof(linea), file)) {
		char cedula[15], f[20], h[10];
		int codigo;
		
		sscanf(linea, "%[^;];%d;%[^;];%s",
			   cedula, &codigo, f, h);
		
		if (codigo == codigoMedico &&
			strcmp(f, fecha) == 0 &&
			strcmp(h, hora) == 0) {
			fclose(file);
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}


// ASIGNAR CITA
void asignarCita() {
	char cedula[15], fecha[20], hora[10];
	int codigoMedico;
	
	printf("\n=== Asignar Cita ===\n");
	printf("Cedula del paciente: ");
	scanf("%s", cedula);
	
	printf("Codigo del medico: ");
	scanf("%d", &codigoMedico);
	
	printf("Fecha (YYYY-MM-DD): ");
	scanf("%s", fecha);
	
	printf("Hora (HH:MM): ");
	scanf("%s", hora);
	
	if (citaOcupada(codigoMedico, fecha, hora)) {
		printf("\nERROR: El medico ya tiene una cita en ese horario.\n");
		return;
	}
	
	FILE *file = fopen(ARCHIVO_CITAS, "a");
	if (!file) {
		printf("Error al abrir archivo de citas.\n");
		return;
	}
	
	fprintf(file, "%s;%d;%s;%s\n",
			cedula, codigoMedico, fecha, hora);
	
	fclose(file);
	
	printf("\nCita asignada correctamente.\n");
}


// CANCELAR CITA
void cancelarCita() {
	char cedula[15], fecha[20], hora[10];
	int codigoMedico;
	int encontrado = 0;
	
	printf("\n=== Cancelar Cita ===\n");
	printf("Cedula del paciente: ");
	scanf("%s", cedula);
	
	printf("Codigo del medico: ");
	scanf("%d", &codigoMedico);
	
	printf("Fecha: ");
	scanf("%s", fecha);
	
	printf("Hora: ");
	scanf("%s", hora);
	
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen("data/temp_citas.txt", "w");
	FILE *log = fopen(ARCHIVO_SEGUIMIENTO, "a");
	
	if (!file || !temp || !log) {
		printf("Error al abrir archivos.\n");
		return;
	}
	
	char linea[256];
	
	while (fgets(linea, sizeof(linea), file)) {
		char c[15], f[20], h[10];
		int cod;
		
		sscanf(linea, "%[^;];%d;%[^;];%s",
			   c, &cod, f, h);
		
		if (strcmp(c, cedula) == 0 &&
			cod == codigoMedico &&
			strcmp(f, fecha) == 0 &&
			strcmp(h, hora) == 0) {
			
			encontrado = 1;
			fprintf(log, "CANCELADA;%s;%d;%s;%s\n",
					cedula, codigoMedico, fecha, hora);
			continue;
		}
		
		fputs(linea, temp);
	}
	
	fclose(file);
	fclose(temp);
	fclose(log);
	
	if (!encontrado) {
		printf("\nCita no encontrada.\n");
		remove("data/temp_citas.txt");
		return;
	}
	
	remove(ARCHIVO_CITAS);
	rename("data/temp_citas.txt", ARCHIVO_CITAS);
	
	printf("\nCita cancelada correctamente.\n");
}


// REPROGRAMAR CITA
void reprogramarCita() {
	char cedula[15], fecha[20], hora[10];
	char nuevaFecha[20], nuevaHora[10];
	int codigoMedico;
	int encontrado = 0;
	
	printf("\n=== Reprogramar Cita ===\n");
	printf("Cedula del paciente: ");
	scanf("%s", cedula);
	
	printf("Codigo del medico: ");
	scanf("%d", &codigoMedico);
	
	printf("Fecha actual: ");
	scanf("%s", fecha);
	
	printf("Hora actual: ");
	scanf("%s", hora);
	
	printf("Nueva fecha: ");
	scanf("%s", nuevaFecha);
	
	printf("Nueva hora: ");
	scanf("%s", nuevaHora);
	
	if (citaOcupada(codigoMedico, nuevaFecha, nuevaHora)) {
		printf("\nERROR: El medico ya tiene una cita en ese nuevo horario.\n");
		return;
	}
	
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen("data/temp_citas.txt", "w");
	FILE *log = fopen(ARCHIVO_SEGUIMIENTO, "a");
	
	if (!file || !temp || !log) {
		printf("Error al abrir archivos.\n");
		return;
	}
	
	char linea[256];
	
	while (fgets(linea, sizeof(linea), file)) {
		char c[15], f[20], h[10];
		int cod;
		
		sscanf(linea, "%[^;];%d;%[^;];%s",
			   c, &cod, f, h);
		
		if (strcmp(c, cedula) == 0 &&
			cod == codigoMedico &&
			strcmp(f, fecha) == 0 &&
			strcmp(h, hora) == 0) {
			
			encontrado = 1;
			
			fprintf(temp, "%s;%d;%s;%s\n",
					cedula, codigoMedico, nuevaFecha, nuevaHora);
			
			fprintf(log, "REPROGRAMADA;%s;%d;%s;%s\n",
					cedula, codigoMedico, nuevaFecha, nuevaHora);
			
			continue;
		}
		
		fputs(linea, temp);
	}
	
	fclose(file);
	fclose(temp);
	fclose(log);
	
	if (!encontrado) {
		printf("\nCita no encontrada.\n");
		remove("data/temp_citas.txt");
		return;
	}
	
	remove(ARCHIVO_CITAS);
	rename("data/temp_citas.txt", ARCHIVO_CITAS);
	
	printf("\nCita reprogramada correctamente.\n");
}
