#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID;// Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // Entre 10 – 100
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

int main() {
    struct Nodo *TareasPendientes;
    struct Nodo *TareasRealizadas;

    return 0;
}