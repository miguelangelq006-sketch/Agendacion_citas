#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "medicos.h"

#define ARCHIVO_MEDICOS "data/medicos.txt"
#define LINEA_MAX 256

//   VERIFICAR SI EL CÓDIGO YA EXISTE
int codigoExiste(int codigo) {
	FILE *file = fopen(ARCHIVO_MEDICOS, "r");
	if (!file) return 0;
	
	char linea[LINEA_MAX];
	while (fgets(linea, sizeof(linea), file)) {
		char copia[LINEA_MAX];
		strcpy(copia, linea);
		
		char *token = strtok(copia, ";");  // código
		if (token && atoi(token) == codigo) {
			fclose(file);
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}

//   REGISTRAR MÉDICO
void registrarMedico() {
	Medico m;
	
	printf("\n=== Registro de Medico ===\n");
	
	// Código del médico
	printf("Codigo del medico: ");
	scanf("%d", &m.codigo);
	
	if (codigoExiste(m.codigo)) {
		printf("\nERROR: Ya existe un medico con ese codigo.\n");
		while (getchar() != '\n');
		return;
	}
	

	while (getchar() != '\n');
	
	// Nombre
	printf("Nombre: ");
	fgets(m.nombre, sizeof(m.nombre), stdin);
	m.nombre[strcspn(m.nombre, "\n")] = '\0';
	
	// Especialidad
	printf("Especialidad: ");
	fgets(m.especialidad, sizeof(m.especialidad), stdin);
	m.especialidad[strcspn(m.especialidad, "\n")] = '\0';
	
	if (strlen(m.especialidad) == 0) {
		printf("\nERROR: La especialidad no puede estar vacia.\n");
		return;
	}
	
	// Horario
	printf("Horario disponible (Ej: 08:00-12:00): ");
	fgets(m.horario, sizeof(m.horario), stdin);
	m.horario[strcspn(m.horario, "\n")] = '\0';
	

	FILE *file = fopen(ARCHIVO_MEDICOS, "a");
	if (!file) {
		printf("\nERROR: No se pudo abrir el archivo de medicos.\n");
		return;
	}
	
	fprintf(file, "%d;%s;%s;%s\n",
			m.codigo, m.nombre, m.especialidad, m.horario);
	
	fclose(file);
	
	printf("\nMedico registrado correctamente.\n");
}


//   LISTAR MÉDICOS
void listarMedicos() {
	FILE *file = fopen(ARCHIVO_MEDICOS, "r");
	if (!file) {
		printf("\nNo hay medicos registrados.\n");
		return;
	}
	
	char linea[LINEA_MAX];
	printf("\n=== Lista de Medicos ===\n");
	
	while (fgets(linea, sizeof(linea), file)) {

		char copia[LINEA_MAX];
		strcpy(copia, linea);
		
		char *token = strtok(copia, ";"); 
		printf("\nCodigo: %s", token);
		
		token = strtok(NULL, ";"); 
		printf("\nNombre: %s", token);
		
		token = strtok(NULL, ";"); 
		printf("\nEspecialidad: %s", token);
		
		token = strtok(NULL, ";\n"); 
		printf("\nHorario: %s\n", token);
		
		printf("--------------------------\n");
	}
	
	fclose(file);
}


