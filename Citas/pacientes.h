#ifndef PACIENTES_H
#define PACIENTES_H

#include "estructuras.h"

void registrarPaciente();
void listarPacientes();
int cedulaExiste(const char *cedula);
int existePaciente(const char cedulaBuscada[]);


#endif
