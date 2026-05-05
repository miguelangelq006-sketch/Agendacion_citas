#include <stdio.h>
#include <string.h>

#include "citas.h"
#include "estructuras.h"
#include "validaciones.h"
#include "medicos.h"
#include "pacientes.h"

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
	
	// -------------------------
	// VERIFICAR MEDICOS
	// -------------------------
	if (!existenMedicos()) {
		printf("ERROR: No hay medicos registrados.\n");
		return;
	}
	
	Cita c;
	strcpy(c.cedulaPaciente, cedulaPaciente);
	
	// -------------------------
	// ESPECIALIDAD
	// -------------------------
	int esp;
	
	while (1) {
		printf("\nSeleccione especialidad:\n");
		printf("1. General\n");
		printf("2. Cardiologia\n");
		printf("3. Pediatria\n");
		printf("4. Traumatologia\n");
		printf("5. Dermatologia\n");
		printf("Opcion: ");
		
		esp = leerEnteroPositivo();
		
		if (esp < 1 || esp > 5) {
			printf("ERROR: Opcion invalida.\n");
			continue;
		}
		
		// Mostrar médicos
		if (!listarMedicosPorEspecialidad(esp)) {
			printf("Seleccione otra especialidad.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// SELECCIONAR MEDICO
	// -------------------------
	while (1) {
		printf("Ingrese codigo del medico: ");
		c.codigoMedico = leerEnteroPositivo();
		
		if (!existeMedico(c.codigoMedico)) {
			printf("ERROR: Medico no existe.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// FECHA
	// -------------------------
	while (1) {
		leerCadenaSoloNumeros("Fecha (YYYYMMDD): ", c.fecha, sizeof(c.fecha));
		
		if (strlen(c.fecha) != 8) {
			printf("ERROR: Formato invalido.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// HORA
	// -------------------------
	while (1) {
		leerCadenaSoloNumeros("Hora (HHMM): ", c.hora, sizeof(c.hora));
		
		if (strlen(c.hora) != 4) {
			printf("ERROR: Formato invalido.\n");
			continue;
		}
		
		break;
	}
	
	// -------------------------
	// VALIDAR CONFLICTOS
	// -------------------------
	if (existeConflicto(c.codigoMedico, c.fecha, c.hora)) {
		printf("ERROR: El medico ya tiene una cita en ese horario.\n");
		return;
	}
	
	if (conflictoPaciente(cedulaPaciente, c.fecha, c.hora)) {
		printf("ERROR: Usted ya tiene una cita en ese horario.\n");
		return;
	}
	
	// -------------------------
	// GUARDAR
	// -------------------------
	strcpy(c.estado, "PENDIENTE");
	
	FILE *file = fopen("data/citas.txt", "a");
	
	if (!file) {
		printf("ERROR al abrir archivo.\n");
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
	
	int total = listarCitasPendientesIndexadas(cedulaPaciente);
	
	if (total == 0) return;
	
	int opcion;
	
	while (1) {
		printf("Seleccione el numero de la cita a cancelar: ");
		opcion = leerEnteroPositivo();
		
		if (opcion < 1 || opcion > total) {
			printf("ERROR: Opcion invalida.\n");
			continue;
		}
		
		break;
	}
	
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen(ARCHIVO_TEMP, "w");
	
	if (!file || !temp) {
		printf("Error con archivos.\n");
		return;
	}
	
	Cita c;
	int contador = 1;
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (strcmp(c.cedulaPaciente, cedulaPaciente) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			if (contador == opcion) {
				strcpy(c.estado, "CANCELADA");
			}
			
			contador++;
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
	
	printf("Cita cancelada correctamente.\n");
}

/* ==========================
REPROGRAMAR CITA
========================== */
void reprogramarCita(const char cedulaPaciente[]) {
	
	int total = listarCitasPendientesIndexadas(cedulaPaciente);
	
	if (total == 0) return;
	
	int opcion;
	
	while (1) {
		printf("Seleccione el numero de la cita a reprogramar: ");
		opcion = leerEnteroPositivo();
		
		if (opcion < 1 || opcion > total) {
			printf("ERROR: Opcion invalida.\n");
			continue;
		}
		
		break;
	}
	
	FILE *file = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen(ARCHIVO_TEMP, "w");
	
	if (!file || !temp) {
		printf("Error con archivos.\n");
		return;
	}
	
	Cita c;
	int contador = 1;
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (strcmp(c.cedulaPaciente, cedulaPaciente) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			if (contador == opcion) {
				
				char nuevaFecha[15], nuevaHora[10];
				
				// NUEVA FECHA
				while (1) {
					leerCadenaSoloNumeros("Nueva Fecha (YYYYMMDD): ", nuevaFecha, sizeof(nuevaFecha));
					
					if (!validarFecha(nuevaFecha)) {
						printf("ERROR: Fecha invalida.\n");
						continue;
					}
					
					break;
				}
				
				// NUEVA HORA
				while (1) {
					leerCadenaSoloNumeros("Nueva Hora (HHMM): ", nuevaHora, sizeof(nuevaHora));
					
					if (!validarHora(nuevaHora)) {
						printf("ERROR: Hora invalida.\n");
						continue;
					}
					
					break;
				}
				
				// VALIDACIONES
				if (existeConflicto(c.codigoMedico, nuevaFecha, nuevaHora)) {
					printf("ERROR: El medico ya tiene una cita en ese horario.\n");
				} else if (conflictoPaciente(cedulaPaciente, nuevaFecha, nuevaHora)) {
					printf("ERROR: Usted ya tiene una cita en ese horario.\n");
				} else {
					strcpy(c.fecha, nuevaFecha);
					strcpy(c.hora, nuevaHora);
					printf("Cita reprogramada correctamente.\n");
				}
			}
			
			contador++;
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

int existeMedico(int codigo) {
	FILE *file = fopen("data/medicos.txt", "r");
	if (!file) return 0;
	
	Medico m;
	
	while (fscanf(file, "%d;%[^;];%d;%[^\n]\n",
				  &m.codigo, m.nombre, &m.especialidad, m.horario) == 4) {
		if (m.codigo == codigo) {
			fclose(file);
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}

int conflictoPaciente(const char cedula[], char fecha[], char hora[]) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) return 0;
	
	Cita c;
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (strcmp(c.cedulaPaciente, cedula) == 0 &&
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

int listarCitasPendientesIndexadas(const char cedula[]) {
	FILE *file = fopen("data/citas.txt", "r");
	if (!file) {
		printf("No hay citas registradas.\n");
		return 0;
	}
	
	Cita c;
	int i = 1;
	int hay = 0;
	
	printf("\n=== TUS CITAS PENDIENTES ===\n");
	
	while (fscanf(file, "%[^;];%d;%[^;];%[^;];%[^\n]\n",
				  c.cedulaPaciente,
				  &c.codigoMedico,
				  c.fecha,
				  c.hora,
				  c.estado) == 5) {
		
		if (strcmp(c.cedulaPaciente, cedula) == 0 &&
			strcmp(c.estado, "PENDIENTE") == 0) {
			
			printf("%d. Medico: %d | Fecha: %s | Hora: %s\n",
				   i, c.codigoMedico, c.fecha, c.hora);
			
			i++;
			hay = 1;
		}
	}
	
	fclose(file);
	
	if (!hay) {
		printf("No tienes citas pendientes.\n");
		return 0;
	}
	
	return i - 1; // cantidad de citas
}
