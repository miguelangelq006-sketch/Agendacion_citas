#ifndef MEDICOS_H
#define MEDICOS_H

typedef struct {
	int codigo;
	char nombre[50];
	int especialidad; // 1 a 5
	char horario[20];
} Medico;

// funciones
void registrarMedico();
void listarMedicos();
void listarMedicosPorEspecialidad(int especialidad);
int existenMedicos();

#endif


