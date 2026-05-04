#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "validaciones.h"

//VALIDAR SOLO LETRAS Y ESPACIOS
int leerSoloLetras(char texto[], int tam) {
	fgets(texto, tam, stdin);
	texto[strcspn(texto, "\n")] = '\0';
	
	if (strlen(texto) == 0) {
		return 0;
	}
	
	for (int i = 0; texto[i] != '\0'; i++) {
		if (!isalpha(texto[i]) && texto[i] != ' ') {
			return 0;
		}
	}
	
	return 1;
}

// VALIDAR ENTERO POSITIVO
int leerEnteroPositivo() {
	char buffer[50];
	int num;
	
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		if (strlen(buffer) == 0) {
			printf("Entrada vacia. Intente de nuevo: ");
			continue;
		}
		
		int valido = 1;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (!isdigit(buffer[i])) {
				valido = 0;
				break;
			}
		}
		
		if (!valido) {
			printf("Solo numeros positivos. Intente de nuevo: ");
			continue;
		}
		
		num = atoi(buffer);
		if (num < 0) {
			printf("Debe ser mayor que 0. Intente de nuevo: ");
			continue;
		}
		
		return num;
	}
}
void leerCadenaSoloNumeros(const char mensaje[], char salida[], int tam) {
	while (1) {
		printf("%s", mensaje);
		fgets(salida, tam, stdin);
		salida[strcspn(salida, "\n")] = '\0';
		
		if (strlen(salida) == 0) {
			printf("ERROR: No puede estar vacio.\n");
			continue;
		}
		
		if (esSoloNumeros(salida)) {
			return;
		}
		
		printf("ERROR: Ingrese solo numeros.\n");
	}
}

int esSoloNumeros(const char cadena[]) {
	for (int i = 0; cadena[i] != '\0'; i++) {
		if (!isdigit(cadena[i])) {
			return 0;
		}
	}
	return 1;
}

void leerCadena(char *dest, int tam) {
	fgets(dest, tam, stdin);
	dest[strcspn(dest, "\n")] = '\0';
}

int validarFecha(const char fecha[]) {
	// Debe tener 8 caracteres
	if (strlen(fecha) != 8) return 0;
	
	// Verificar que sean números
	for (int i = 0; i < 8; i++) {
		if (!isdigit(fecha[i])) return 0;
	}
	
	// Extraer valores
	int anio = (fecha[0]-'0')*1000 + (fecha[1]-'0')*100 + (fecha[2]-'0')*10 + (fecha[3]-'0');
	int mes  = (fecha[4]-'0')*10 + (fecha[5]-'0');
	int dia  = (fecha[6]-'0')*10 + (fecha[7]-'0');
	
	// Validar año
	if (anio < 1900 || anio > 2100) return 0;
	
	// Validar mes
	if (mes < 1 || mes > 12) return 0;
	
	// Días por mes
	int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	// Año bisiesto
	if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
		diasMes[1] = 29;
	}
	
	// Validar día
	if (dia < 1 || dia > diasMes[mes - 1]) return 0;
	
	return 1;
}

int validarHora(const char hora[]) {
	if (strlen(hora) != 4) return 0;
	
	for (int i = 0; i < 4; i++) {
		if (!isdigit(hora[i])) return 0;
	}
	
	int hh = (hora[0]-'0')*10 + (hora[1]-'0');
	int mm = (hora[2]-'0')*10 + (hora[3]-'0');
	
	if (hh < 0 || hh > 23) return 0;
	if (mm < 0 || mm > 59) return 0;
	
	return 1;
}
