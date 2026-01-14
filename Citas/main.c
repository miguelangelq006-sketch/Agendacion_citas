#include <stdio.h>
#include <stdlib.h>

#include "autenticacion.h"
#include "pacientes.h"
#include "medicos.h"
#include "citas.h"

int main() {
	int opcion;
	
	// AUTENTICACION
	if (!login()) {
		printf("\nAcceso denegado.\n");
		return 0;
	}
	
	do {
		printf("\n===== SISTEMA DE CITAS MEDICAS =====\n");
		printf("1. Registrar paciente\n");
		printf("2. Listar pacientes\n");
		printf("3. Registrar medico\n");
		printf("4. Listar medicos\n");
		printf("5. Asignar cita\n");
		printf("6. Cancelar cita\n");
		printf("7. Reprogramar cita\n");
		printf("0. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
		case 1:
			registrarPaciente();
			break;
			
		case 2:
			listarPacientes();
			break;
			
		case 3:
			registrarMedico();
			break;
			
		case 4:
			listarMedicos();
			break;
			
		case 5:
			asignarCita();
			break;
			
		case 6:
			cancelarCita();
			break;
			
		case 7:
			reprogramarCita();
			break;
			
		case 0:
			printf("\nSaliendo del sistema...\n");
			break;
			
		default:
			printf("\nOpcion invalida.\n");
		}
		
	} while (opcion != 0);
	
	return 0;
}


