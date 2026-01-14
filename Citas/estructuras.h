#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct {
	char nombre[50];
	char cedula[11];
	int edad;
	char telefono[15];
	char correo[50];
} Paciente;

typedef struct {
	int codigo;
	char nombre[50];
	char especialidad[50];
	char horario[30];
} Medico;

typedef struct {
	char cedulaPaciente[11];
	int codigoMedico;
	char fecha[11];
	char hora[6];
} Cita;

#endif
