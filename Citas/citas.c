#include <stdio.h>
#include <string.h>

#include "estructuras.h"
#include "citas.h"
#include "pacientes.h"
#include "medicos.h"

/* ==========================
VALIDAR CONFLICTO
========================== */
int existeConflicto(int codigoMedico, char fecha[], char hora[]) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) return 0;
	
	Cita c;
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) != EOF) {
		
		if (c.codigoMedico == codigoMedico &&
			strcmp(c.fecha, fecha) == 0 &&
			strcmp(c.hora, hora) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			fclose(file);
			return 1; // conflicto
		}
	}
	
	fclose(file);
	return 0;
}

/* ==========================
AGENDAR CITA
========================== */
void agendarCita(const char cedulaPaciente[]) {
	Cita c;
	int especialidad;
	
	printf("\n=== Asignar Cita ===\n");
	printf("Cedula del paciente: ");
	sprintf(cedula, "%d", leerEnteroPositivo());
	
	
	printf("Especialidad: ");
	especialidad = leerEnteroPositivo();
	
	while (especialidad < 1 || especialidad > 5) {
		printf("Especialidad invalida (1-5): ");
		especialidad = leerEnteroPositivo();
	}
	
	
	printf("Codigo del medico: ");
	codigoMedico = leerEnteroPositivo();
	

	
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
	sprintf(cedula, "%d", leerEnteroPositivo());
	
	printf("Codigo del medico: ");
	codigoMedico = leerEnteroPositivo();
	
	printf("Especialidad: ");
	especialidad = leerEnteroPositivo();
	
	while (especialidad < 1 || especialidad > 5) {
		printf("Especialidad invalida (1-5): ");
		especialidad = leerEnteroPositivo();
	}
	
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

		
		if (strcmp(c.cedulaPaciente, cedulaPaciente) == 0 &&
			c.codigoMedico == codigo &&
			strcmp(c.fecha, fecha) == 0 &&
			strcmp(c.hora, hora) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			strcpy(c.estado, "CANCELADA");
			encontrada = 1;
		}
		
		fprintf(temp, "%s;%d;%s;%s;%s\n",
				c.cedulaPaciente,
				c.codigoMedico,
				c.fecha,
				c.hora,
				c.estado);
	}
	
	fclose(file);
	fclose(temp);
	
	remove("data/citas.txt");
	rename("data/temp.txt", "data/citas.txt");
	
	if (encontrada)
		printf("Cita cancelada correctamente.\n");
	else
		printf("Cita no encontrada o no pendiente.\n");
	
}


/* ==========================
REPROGRAMAR CITA
========================== */
void reprogramarCita(const char cedulaPaciente[]) {
	FILE *file = fopen("data/citas.txt", "r");
	FILE *temp = fopen("data/temp.txt", "w");
	
	if (!file || !temp) {
		printf("Error con archivos.\n");
		return;
	}
	
	char cedula[15];
	int codigo;
	char fecha[15], hora[10];
	Cita c;
	int encontrada = 0;
	
	printf("Cedula del paciente: ");
	sprintf(cedula, "%d", leerEnteroPositivo());
	
	printf("Especialidad: ");
	especialidad = leerEnteroPositivo();
	
	while (especialidad < 1 || especialidad > 5) {
		printf("Especialidad invalida (1-5): ");
		especialidad = leerEnteroPositivo();
	}
	
	printf("Codigo del medico: ");

	codigoMedico = leerEnteroPositivo();

	
	printf("Fecha actual: ");
	scanf("%s", fecha);
	
	printf("Hora actual: ");
	scanf("%s", hora);
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) != EOF) {
		
		if (strcmp(c.cedulaPaciente, cedula) == 0 &&
			c.codigoMedico == codigo &&
			strcmp(c.fecha, fecha) == 0 &&
			strcmp(c.hora, hora) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			printf("Nueva fecha: ");
			scanf("%s", c.fecha);
			
			printf("Nueva hora: ");
			scanf("%s", c.hora);
			
			if (existeConflicto(c.codigoMedico, c.fecha, c.hora)) {
				printf("Nuevo horario no disponible.\n");
			} else {
				encontrada = 1;
			}
		}
		
		fprintf(temp, "%s;%d;%s;%s;%s\n",
				c.cedulaPaciente,
				c.codigoMedico,
				c.fecha,
				c.hora,
				c.estado);
	}
	
	fclose(file);
	fclose(temp);
	
	remove("data/citas.txt");
	rename("data/temp.txt", "data/citas.txt");
	
	if (encontrada)
		printf("Cita reprogramada.\n");
	else
		printf("Cita no encontrada.\n");
}

/* ==========================
LISTAR CITAS POR MEDICO
========================== */
void listarCitasPendientesPorMedico(int codigoMedico) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) return;
	
	Cita c;
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente, &c.codigoMedico,
				  c.fecha, c.hora, c.estado) == 5) {
		
		if (c.codigoMedico == codigoMedico &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			printf("Paciente: %s | %s %s\n",
				   c.cedulaPaciente, c.fecha, c.hora);
		}
	}
	fclose(file);
}

void listarTodasLasCitasPorMedico(int codigoMedico) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) return;
	
	Cita c;
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente, &c.codigoMedico,
				  c.fecha, c.hora, c.estado) == 5) {
		
		if (c.codigoMedico == codigoMedico) {
			printf("Paciente: %s | %s %s | %s\n",
				   c.cedulaPaciente, c.fecha, c.hora, c.estado);
		}
	}
	fclose(file);
}

/* ==========================
LISTAR CITAS POR PACIENTE
========================== */
void listarCitasPendientesPorPaciente(const char cedula[]) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return;
	}
	
	Cita c;
	int hay = 0;
	
	printf("\n=== MIS CITAS PENDIENTES ===\n");
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (strcmp(c.cedulaPaciente, cedula) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			printf("Medico: %d | Fecha: %s | Hora: %s\n",
				   c.codigoMedico, c.fecha, c.hora);
			hay = 1;
		}
	}
	
	if (!hay) {
		printf("No tienes citas pendientes.\n");
	}
	
	fclose(file);
}
void listarTodasLasCitasPorPaciente(const char cedula[]) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return;
	}
	
	Cita c;
	int hay = 0;
	
	printf("\n=== HISTORIAL DE MIS CITAS ===\n");
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (strcmp(c.cedulaPaciente, cedula) == 0) {
			printf("Medico: %d | Fecha: %s | Hora: %s | Estado: %s\n",
				   c.codigoMedico, c.fecha, c.hora, c.estado);
			hay = 1;
		}
	}
	
	if (!hay) {
		printf("No tienes citas registradas.\n");
	}
	
	fclose(file);
}
