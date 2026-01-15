int existePaciente(char cedulaBuscada[]) {
	FILE *file = fopen("data/pacientes.txt", "r");
	if (!file) return 0;
	
	char cedula[15], nombre[50], telefono[15];
	int edad;
	
	while (fscanf(file, "%[^;];%[^;];%d;%s\n",
				  cedula, nombre, &edad, telefono) != EOF) {
		if (strcmp(cedula, cedulaBuscada) == 0) {
			fclose(file);
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}


