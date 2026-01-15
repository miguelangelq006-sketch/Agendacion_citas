#include <stdio.h>

int listarMedicosPorEspecialidad(int esp) {
	FILE *file = fopen("data/medicos.txt", "r");
	if (!file) {
		printf("No hay medicos registrados.\n");
		return 0; // no existe archivo
	}
	
	int codigo, especialidad;
	char nombre[50], horario[20];
	int encontrados = 0;
	
	while (fscanf(file, "%d;%[^;];%d;%[^\n]\n",
				  &codigo, nombre, &especialidad, horario) != EOF) {
		
		if (especialidad == esp) {
			printf("Codigo: %d | Nombre: %s | Horario: %s\n",
				   codigo, nombre, horario);
			encontrados = 1;
		}
	}
	
	fclose(file);
	
	if (!encontrados) {
		printf("No hay medicos de esa especialidad.\n");
		return 0;
	}
	
	return 1; // hay médicos válidos
}
