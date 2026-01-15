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
	
	Cita c	;
	
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
void agendarCita() {
	FILE *file;
	Cita c;
	int especialidad;
	
	printf("Cedula del paciente: ");
	scanf("%s", c.cedulaPaciente);
	
	if (!existePaciente(c.cedulaPaciente)) {
		printf("Paciente no registrado.\n");
		return;
	}
	
	printf("Especialidad:\n");
	printf("1. General\n2. Cardiologia\n3. Pediatria\n4. Traumatologia\n5. Dermatologia\n");
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
	
	file = fopen("data/citas.txt", "a");
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
void cancelarCita() {
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
	
	printf("Fecha: ");
	scanf("%s", fecha);
	
	printf("Hora: ");
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
		printf("Cita no encontrada.\n");
}

/* ==========================
REPROGRAMAR CITA
========================== */
void reprogramarCita() {
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
void listarCitasPorMedico(int codigoMedico) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return;
	}
	
	Cita c;
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) != EOF) {
		
		if (c.codigoMedico == codigoMedico &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			printf("Paciente: %s | Fecha: %s | Hora: %s\n",
				   c.cedulaPaciente, c.fecha, c.hora);
		}
	}
	
	fclose(file);
}

/* ==========================
LISTAR CITAS POR PACIENTE
========================== */
void listarCitasPorPaciente(char cedula[]) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return;
	}
	
	Cita c;
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) != EOF) {
		
		if (strcmp(c.cedulaPaciente, cedula) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			printf("Medico: %d | Fecha: %s | Hora: %s\n",
				   c.codigoMedico, c.fecha, c.hora);
		}
	}
	
	fclose(file);
}
