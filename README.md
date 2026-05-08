# Sistema de Agendamiento de Citas Médicas

Este es un sistema tipo TPS (Transaction Processing System) desarrollado en lenguaje C para la gestión de citas médicas en un centro de salud. El sistema permite administrar pacientes, médicos y citas mediante una interfaz basada en menús y validaciones de datos.

## Funcionalidades

- Registro de pacientes
- Registro de médicos
- Agendamiento de citas por especialidad
- Cancelación de citas
- Reprogramación de citas
- Validación de fechas y horarios
- Control de conflictos de citas
- Reportes básicos del sistema
- Gestión por roles (Administrador, Médico y Paciente)

---

## Tecnologías utilizadas

- Lenguaje C
- Archivos `.txt` para persistencia de datos
- ZinjaI / GCC

---

## Estructura del proyecto

```txt
├── main.c
├── pacientes.c
├── medicos.c
├── citas.c
├── reportes.c
├── validaciones.c
├── data/
│   ├── pacientes.txt
│   ├── medicos.txt
│   ├── cuentas.txt
│   └── citas.txt
```

---

## Cómo ejecutar el proyecto
Existen dos formas de obtener y ejecutar el proyecto: clonando el repositorio con Git o descargándolo manualmente desde GitHub.

### Opción 1: Clonar el repositorio con Git

1. Abrir Git Bash, CMD o la terminal.
2. Ejecutar el siguiente comando:

```bash
git clone https://github.com/miguelangelq006-sketch/Agendacion_citas.git //(URL_DEL_REPOSITORIO)
```

3. Ingresar a la carpeta del proyecto:

```bash
cd Agendacion_citas
```

4. Abrir la carpeta del proyecto en ZinjaI o en el entorno de desarrollo de preferencia.

5. Verificar que exista la carpeta `data` junto con los archivos:
   - `pacientes.txt`
   - `medicos.txt`
   - `citas.txt`
   - `cuentas.txt`

   Si no existen, crearlos vacíos dentro de la carpeta `data`.

6. Compilar el proyecto desde ZinjaI o usando GCC.

7. Ejecutar el archivo principal (`main.c`).

---

### Opción 2: Descargar el proyecto manualmente

1. Ingresar al repositorio en GitHub.
2. Presionar el botón verde:

```txt
Code
```

3. Seleccionar:

```txt
Download ZIP
```

4. Extraer el archivo `.zip` en una carpeta del computador.

5. Abrir la carpeta del proyecto en ZinjaI.

6. Verificar que exista la carpeta `data` con los archivos:
   - `pacientes.txt`
   - `medicos.txt`
   - `citas.txt`
   - `cuentas.txt`

7. Compilar y ejecutar el proyecto desde `main.c`.

---


## Roles del sistema

### Administrador
- Registrar pacientes
- Registrar médicos
- Consultar reportes

### Paciente
- Agendar citas
- Cancelar citas
- Reprogramar citas
- Ver historial

### Médico
- Consultar citas asignadas

---

## Validaciones implementadas

- Validación de cédula
- Validación de entradas numéricas
- Validación de fechas reales
- Validación de horas válidas
- Prevención de citas duplicadas
- Verificación de disponibilidad médica

---

## 📊 Tipo de sistema

Sistema TPS orientado al procesamiento y control de transacciones médicas relacionadas con la gestión de citas en un centro de salud.

---

## Autores

- Miguel Quiroz
- Ismael Salazar
- Ariel Guachamin

Proyecto académico desarrollado para la asignatura de Programación.
