#ifndef VALIDACIONES_H
#define VALIDACIONES_H



int leerSoloLetras(char texto[], int tam);
int leerEnteroPositivo();
int esSoloNumeros(const char cadena[]);
void leerCadenaSoloNumeros(const char mensaje[], char salida[], int tam);
void leerCadena(char *dest, int tam);
int validarFecha(const char fecha[]);
int validarHora(const char hora[]);

#endif
