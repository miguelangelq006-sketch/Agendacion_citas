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
	
	strcpy(c.cedulaPaciente, cedulaPaciente);
	
	if (!existenMedicos()) {
		printf("ERROR: No existen medicos registrados.\n");
		return;
	}
	
	printf("Especialidad:\n");
	printf("1. General\n2. Cardiologia\n3. Pediatria\n");
	printf("4. Traumatologia\n5. Dermatologia\n");
	printf("Seleccione: ");
	scanf("%d", &especialidad);
	
	if (!listarMedicosPorEspecialidad(especialidad)) {
		return;
	}
	
	printf("Codigo del medico: ");
	scanf("%d", &c.codigoMedico);
	
	printf("Fecha (YYYY-MM-DD): ");
	scanf("%s", c.fecha);
	
	printf("Hora (HH:MM): ");
	scanf("%s", c.hora);
	
	if (existeConflicto(c.codigoMedico, c.fecha, c.hora)) {
		printf("Horario no disponible.\n");
		return;
	}
	
	strcpy(c.estado, "PENDIENTE");
	
	FILE *file = fopen("data/citas.txt", "a");
	if (!file) {
		printf("Error al abrir archivo de citas.\n");
		return;
	}
	
	fprintf(file, "%s;%d;%s;%s;%s\n",
			c.cedulaPaciente,
			c.codigoMedico,
			c.fecha,
			c.hora,
			c.estado);
	
	fclose(file);
	printf("Cita agendada correctamente.\n");
}


/* ==========================
CANCELAR CITA
========================== */
void cancelarCita(const char cedulaPaciente[]) {
	FILE *file = fopen("data/citas.txt", "r");
	FILE *temp = fopen("data/temp.txt", "w");
	
	if (!file || !temp) {
		printf("Error con archivos.\n");
		return;
	}
	
	int codigo;
	char fecha[15], hora[10];
	Cita c;
	int encontrada = 0;
	
	printf("Codigo del medico: ");
	scanf("%d", &codigo);
	
	printf("Fecha (YYYY-MM-DD): ");
	scanf("%s", fecha);
	
	printf("Hora (HH:MM): ");
	scanf("%s", hora);
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
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
	scanf("%s", cedula);
	
	printf("Codigo del medico: ");
	scanf("%d", &codigo);
	
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
