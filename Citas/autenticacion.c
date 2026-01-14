#include <stdio.h>
#include <string.h>
#include "autenticacion.h"

int iniciarSesion() {
	char usuarioCorrecto[] = "usuario";
	char claveCorrecta[] = "1234";
	
	char usuarioIngresado[20];
	char claveIngresada[20];
	
	int intentos = 3;
	
	while (intentos > 0) {
		printf("\n=== INICIO DE SESION ===\n");
		printf("Usuario: ");
		scanf("%s", usuarioIngresado);
		
		printf("Contrasena: ");
		scanf("%s", claveIngresada);
		
		if (strcmp(usuarioIngresado, usuarioCorrecto) == 0 &&
			strcmp(claveIngresada, claveCorrecta) == 0) {
			
			printf("\nAcceso concedido. Bienvenido!\n");
			return 1;
		}else{
			intentos--;
			printf("\nDatos incorrectos. Intentos restantes: %d\n", intentos);
		}
		
	}
	
	printf("\nHas superado el numero de intentos. Acceso denegado.\n");
	return 0; 
}
