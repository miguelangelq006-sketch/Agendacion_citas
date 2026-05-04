#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"
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
	
	// -------------------------
	// CODIGO
	// -------------------------
	while (1) {
		printf("Codigo del medico: ");
		m.codigo = leerEnteroPositivo();
		
		if (codigoExiste(m.codigo)) {
			printf("ERROR: Ya existe un medico con ese codigo.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// NOMBRE
	// -------------------------
	do {
		printf("Nombre del medico: ");
	} while (!leerSoloLetras(m.nombre, sizeof(m.nombre)));
	
	// -------------------------
	// ESPECIALIDAD
	// -------------------------
	while (1) {
		printf("\nEspecialidad:\n");
		printf("1. General\n");
		printf("2. Cardiologia\n");
		printf("3. Pediatria\n");
		printf("4. Traumatologia\n");
		printf("5. Dermatologia\n");
		printf("Seleccione una opcion: ");
		
		m.especialidad = leerEnteroPositivo();
		
		if (m.especialidad < 1 || m.especialidad > 5) {
			printf("ERROR: Opcion invalida (1-5).\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// HORARIO
	// -------------------------
	while (1) {
		printf("Horario disponible (Ej: 08:00-12:00): ");
		leerCadena(m.horario, sizeof(m.horario));
		
		// Validación básica de formato
		if (strlen(m.horario) < 5 || strchr(m.horario, '-') == NULL) {
			printf("ERROR: Formato invalido.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// GUARDAR
	// -------------------------
	FILE *file = fopen("data/medicos.txt", "a");
	
	if (!file) {
		printf("\nERROR: No se pudo abrir el archivo de medicos.\n");
		return;
	}
	
	fprintf(file, "%d;%s;%d;%s\n",
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
		int esp = atoi(token);
		
		char *especialidades[] = {
			"General", "Cardiologia", "Pediatria",
				"Traumatologia", "Dermatologia"
		};
		
		if (esp >= 1 && esp <= 5)
			printf("\nEspecialidad: %s", especialidades[esp - 1]);
		else
			printf("\nEspecialidad: Desconocida");
		
		
		token = strtok(NULL, ";\n"); 
		printf("\nHorario: %s\n", token);
		
		printf("--------------------------\n");
	}
	
	fclose(file);
}

int listarMedicosPorEspecialidad(int esp) {
	FILE *file = fopen("data/medicos.txt", "r");
	if (!file) {
		printf("No hay medicos registrados.\n");
		return 0;
	}
	
	Medico m;
	int encontrados = 0;
	
	while (fscanf(file, "%d;%[^;];%d;%[^\n]\n",
				  &m.codigo, m.nombre, &m.especialidad, m.horario) == 4) {
		
		if (m.especialidad == esp) {
			printf("Codigo: %d | %s | Horario: %s\n",
				   m.codigo, m.nombre, m.horario);
			encontrados = 1;
		}
	}
	
	fclose(file);
	
	if (!encontrados) {
		printf("No hay medicos de esa especialidad.\n");
		return 0;
	}
	
	return 1;
}
int existenMedicos() {
	FILE *file = fopen("data/medicos.txt", "r");
	if (!file) return 0;
	
	char linea[5];
	int existe = fgets(linea, sizeof(linea), file) != NULL;
	
	fclose(file);
	return existe;
}



