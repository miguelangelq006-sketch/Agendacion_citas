#ifndef CITAS_H
#define CITAS_H

void agendarCita(const char cedulaPaciente[]);
void cancelarCita(const char cedulaPaciente[]);
void reprogramarCita(const char cedulaPaciente[]);
void listarCitasPendientesPorMedico(int codigoMedico);
void listarTodasLasCitasPorMedico(int codigoMedico);
void listarCitasPendientesPorPaciente(const char cedula[]);
void listarTodasLasCitasPorPaciente(const char cedula[]);
int existeConflicto(int codigoMedico, char fecha[], char hora[]);

#endif
