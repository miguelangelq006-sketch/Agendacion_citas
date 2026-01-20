#include <stdio.h>
#include <stdlib.h>

#include "autenticacion.h"
#include "pacientes.h"
#include "medicos.h"
#include "citas.h"
#include "reportes.h"

/* ROLES */
#define ADMIN 1
#define MEDICO 2
#define PACIENTE 3

void menuAdministrador() {
	int op;
	
	do {
		printf("\n=== MENU ADMINISTRADOR ===\n");
		printf("1. Registrar medico\n");
		printf("2. Listar medicos\n");
		printf("3. Registrar paciente\n");
		printf("4. Listar pacientes\n");
		printf("5. Crear usuario\n");
		printf("6. Reportes\n");
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1:
			registrarMedico();
			break;
		case 2:
			listarMedicos();
			break;
		case 3:
			registrarPaciente();
			break;
		case 4:
			listarPacientes();
			break;
		case 5:
			crearUsuario();
			break;
		case 6:
			menuReportes();
			break;
		case 0:
			printf("Saliendo...\n");
			break;
		default:
			printf("Opcion invalida.\n");
		}
		
	} while (op != 0);
}


void menuMedico(int codigoMedico) {
	int op;
	
	do {
		printf("\n=== MENU MEDICO ===\n");
		printf("1. Ver mis citas pendientes\n");
		printf("2. Ver historial de citas\n");
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1:
			listarCitasPendientesPorMedico(codigoMedico); // PENDIENTES
			break;
		case 2:
			listarTodasLasCitasPorMedico(codigoMedico); // TODAS
			break;
		case 0:
			printf("Saliendo...\n");
			break;
		default:
			printf("Opcion invalida.\n");
		}
		
	} while (op != 0);
}
void menuPaciente(char cedulaPaciente[]) {
	int op;
	
	do {
		printf("\n=== MENU PACIENTE ===\n");
		printf("1. Agendar cita\n");
		printf("2. Cancelar cita\n");
		printf("3. Reprogramar cita\n");
		printf("4. Ver citas pendientes\n");
		printf("5. Ver historial de citas\n");
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1:
			agendarCita(cedulaPaciente);
			break;
		case 2:
			cancelarCita(cedulaPaciente);
			break;
		case 3:
			reprogramarCita(cedulaPaciente);
			break;
		case 4:
			listarCitasPendientesPorPaciente(cedulaPaciente);
			break;
		case 5:
			listarTodasLasCitasPorPaciente(cedulaPaciente);
			break;
		case 0:
			printf("Saliendo...\n");
			break;
		default:
			printf("Opcion invalida.\n");
		}
		
	} while (op != 0);
}

int main() {
	int rol;
	int codigoMedico = 0;
	char cedulaPaciente[15];
	
	printf("=================================\n");
	printf("   SISTEMA DE CITAS MEDICAS\n");
	printf("=================================\n");
	
	/* AUTENTICACIÓN */
	rol = login(&codigoMedico, cedulaPaciente);
	
	if (rol == 0) {
		printf("Acceso denegado.\n");
		return 0;
	}
	
	switch (rol) {
	case ADMIN:
		menuAdministrador();
		break;
		
	case MEDICO:
		menuMedico(codigoMedico);
		break;
		
	case PACIENTE:
		menuPaciente(cedulaPaciente);
		break;
		
	default:
		printf("Rol no valido.\n");
	}
	
	return 0;
}
