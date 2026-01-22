#include <stdio.h>
#include <string.h>

#include "citas.h"
#include "estructuras.h"
#include "validaciones.h"

#define ARCHIVO_CITAS "data/citas.txt"
#define ARCHIVO_TEMP  "data/temp_citas.txt"


/* ==========================
VALIDAR CONFLICTO
========================== */
int existeConflicto(int codigoMedico, char fecha[], char hora[]) {
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	if (!file) return 0;
	
	Cita c;
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (c.codigoMedico == codigoMedico &&
			strcmp(c.fecha, fecha) == 0 &&
			strcmp(c.hora, hora) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			fclose(file);
			return 1;
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
	
	strcpy(c.cedulaPaciente, cedulaPaciente);
	
	printf("Codigo del medico: ");
	c.codigoMedico = leerEnteroPositivo();
	
	leerCadenaSoloNumeros("Fecha (YYYYMMDD): ", c.fecha, sizeof(c.fecha));
	leerCadenaSoloNumeros("Hora (HHMM): ", c.hora, sizeof(c.hora));
	
	if (existeConflicto(c.codigoMedico, c.fecha, c.hora)) {
		printf("ERROR: Horario ocupado.\n");
		return;
	}
	
	strcpy(c.estado, "PENDIENTE");
	
	FILE *file = fopen(ARCHIVO_CITAS, "a");
	if (!file) {
		printf("Error al abrir archivo.\n");
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


// CANCELAR CITA
void cancelarCita(const char cedulaPaciente[]) {
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen(ARCHIVO_TEMP, "w");
	
	if (!file || !temp) {
		printf("Error con archivos.\n");
		return;
	}
	
	char fecha[20], hora[10];
	int codigoMedico;
	int encontrada = 0;
	Cita c;
	
	printf("Codigo del medico: ");
	codigoMedico = leerEnteroPositivo();
	
	leerCadenaSoloNumeros("Fecha: ", fecha, sizeof(fecha));
	leerCadenaSoloNumeros("Hora: ", hora, sizeof(hora));
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (strcmp(c.cedulaPaciente, cedulaPaciente) == 0 &&
			c.codigoMedico == codigoMedico &&
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
	
	remove(ARCHIVO_CITAS);
	rename(ARCHIVO_TEMP, ARCHIVO_CITAS);
	
	if (encontrada)
		printf("Cita cancelada.\n");
	else
		printf("Cita no encontrada.\n");
}



/* ==========================
REPROGRAMAR CITA
========================== */
void reprogramarCita(const char cedulaPaciente[]) {
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen(ARCHIVO_TEMP, "w");
	
	if (!file || !temp) {
		printf("Error con archivos.\n");
		return;
	}
	
	Cita c;
	int encontrada = 0;
	int codigoMedico;
	char fechaActual[20], horaActual[10];
	
	printf("\n=== Reprogramar Cita ===\n");
	
	printf("Codigo del medico: ");
	codigoMedico = leerEnteroPositivo();
	
	leerCadenaSoloNumeros("Fecha actual: ", fechaActual, sizeof(fechaActual));
	leerCadenaSoloNumeros("Hora actual: ", horaActual, sizeof(horaActual));
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		/* Encontrar la cita pendiente del paciente */
		if (strcmp(c.cedulaPaciente, cedulaPaciente) == 0 &&
			c.codigoMedico == codigoMedico &&
			strcmp(c.fecha, fechaActual) == 0 &&
			strcmp(c.hora, horaActual) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			char nuevaFecha[20], nuevaHora[10];
			
			leerCadenaSoloNumeros("Nueva fecha: ", nuevaFecha, sizeof(nuevaFecha));
			leerCadenaSoloNumeros("Nueva hora: ", nuevaHora, sizeof(nuevaHora));
			
			if (existeConflicto(c.codigoMedico, nuevaFecha, nuevaHora)) {
				printf("ERROR: El nuevo horario no esta disponible.\n");
			} else {
				strcpy(c.fecha, nuevaFecha);
				strcpy(c.hora, nuevaHora);
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
	
	remove(ARCHIVO_CITAS);
	rename(ARCHIVO_TEMP, ARCHIVO_CITAS);
	
	if (encontrada)
		printf("Cita reprogramada correctamente.\n");
	else
		printf("Cita no encontrada o no pendiente.\n");
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
