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
	
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		if (strlen(buffer) == 0) {
			printf("Entrada vacia. Intente de nuevo: ");
			continue;
		}
		
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (!isdigit(buffer[i])) {
				printf("Solo numeros enteros positivos. Intente de nuevo: ");
				goto siguiente;
			}
		}
		
		return atoi(buffer);
		
		siguiente:;
	}
}
