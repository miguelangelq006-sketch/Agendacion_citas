#include <stdio.h>
#include <string.h>
#include "reportes.h"

#define ARCHIVO_CITAS "data/citas.txt"
#define MAX 100

typedef struct {
	int codigoMedico;
	int contador;
} ConteoMedico;

typedef struct {
	char cedula[15];
	int contador;
} ConteoPaciente;

void menuReportes() {
	int op;
	
	do {
		printf("\n=== REPORTES ===\n");
		printf("1. Citas por medico\n");
		printf("2. Pacientes con mas de una cita\n");
		printf("3. Medicos con mayor demanda\n");
		printf("0. Volver\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1:
			reporteCitasPorMedico();
			break;
		case 2:
			reportePacientesConMasDeUnaCita();
			break;
		case 3:
			reporteMedicosConMasDemanda();
			break;
		case 0:
			break;
		default:
			printf("Opcion invalida.\n");
		}
	} while (op != 0);
}

void reporteCitasPorMedico() {
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return;
	}
	
	ConteoMedico medicos[MAX];
	int total = 0;
	
	int codigo;
	char cedula[15], fecha[15], hora[10], estado[15];
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  cedula, &codigo, fecha, hora, estado) == 5) {
		
		int encontrado = 0;
		for (int i = 0; i < total; i++) {
			if (medicos[i].codigoMedico == codigo) {
				medicos[i].contador++;
				encontrado = 1;
				break;
			}
		}
		
		if (!encontrado && total < MAX) {
			medicos[total].codigoMedico = codigo;
			medicos[total].contador = 1;
			total++;
		}
	}
	
	fclose(file);
	
	printf("\nCITAS POR MEDICO:\n");
	for (int i = 0; i < total; i++) {
		printf("Medico %d -> %d citas\n",
			   medicos[i].codigoMedico,
			   medicos[i].contador);
	}
}


void reportePacientesConMasDeUnaCita() {
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return;
	}
	
	ConteoPaciente pacientes[MAX];
	int total = 0;
	
	int codigo;
	char cedula[15], fecha[15], hora[10], estado[15];
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  cedula, &codigo, fecha, hora, estado) == 5) {
		
		int encontrado = 0;
		
		for (int i = 0; i < total; i++) {
			if (strcmp(pacientes[i].cedula, cedula) == 0) {
				pacientes[i].contador++;
				encontrado = 1;
				break;
			}
		}
		
		if (!encontrado && total < MAX) {
			strcpy(pacientes[total].cedula, cedula);
			pacientes[total].contador = 1;
			total++;
		}
	}
	
	fclose(file);
	
	printf("\nPACIENTES CON MAS DE UNA CITA:\n");
	int hay = 0;
	
	for (int i = 0; i < total; i++) {
		if (pacientes[i].contador > 1) {
			printf("Paciente %s -> %d citas\n",
				   pacientes[i].cedula,
				   pacientes[i].contador);
			hay = 1;
		}
	}
	
	if (!hay) {
		printf("No existen pacientes con mas de una cita.\n");
	}
}


void reporteMedicosConMasDemanda() {
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return;
	}
	
	ConteoMedico medicos[MAX];
	int total = 0;
	
	int codigo;
	char cedula[15], fecha[15], hora[10], estado[15];
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  cedula, &codigo, fecha, hora, estado) == 5) {
		
		int encontrado = 0;
		
		for (int i = 0; i < total; i++) {
			if (medicos[i].codigoMedico == codigo) {
				medicos[i].contador++;
				encontrado = 1;
				break;
			}
		}
		
		if (!encontrado && total < MAX) {
			medicos[total].codigoMedico = codigo;
			medicos[total].contador = 1;
			total++;
		}
	}
	
	fclose(file);
	
	if (total == 0) {
		printf("No hay datos para generar el reporte.\n");
		return;
	}
	
	int max = medicos[0].contador;
	for (int i = 1; i < total; i++) {
		if (medicos[i].contador > max) {
			max = medicos[i].contador;
		}
	}
	
	printf("\nMEDICOS CON MAYOR DEMANDA (%d citas):\n", max);
	for (int i = 0; i < total; i++) {
		if (medicos[i].contador == max) {
			printf("Medico %d\n", medicos[i].codigoMedico);
		}
	}
}
