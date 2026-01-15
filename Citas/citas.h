#ifndef CITAS_H
#define CITAS_H

void agendarCita();
void cancelarCita();
void reprogramarCita();
void listarCitasPorMedico(int codigoMedico);
void listarCitasPorPaciente(char cedula[]);
int existeConflicto(int codigoMedico, char fecha[], char hora[]);

#endif
