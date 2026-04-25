#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Variables Globales
int TareaIDs = 1000;

// Estructuras
typedef struct Tarea {
    int TareaID;// Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // Entre 10 – 100
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

// Funciones
struct Nodo * CrearNodo(char * Descripcion[]);
void InsertarNodo(struct Nodo ** Start, struct Nodo * VNodo);
void InsertarAlFinal(struct Nodo * Start, struct Nodo * VNodo);
struct Nodo * BuscarNodo(struct Nodo * Start, int IdBuscado);
struct Nodo * QuitarNodo(struct Nodo ** Start, int IdBuscado);
void EliminarNodo(struct Nodo * VNodo);


int main() {
    struct Nodo *TareasPendientes;
    struct Nodo *TareasRealizadas;

    srand(time(NULL)); // Empezar con una semilla distinta para el generador de numeros aleatoreo

    return 0;
}


struct Nodo * CrearNodo(char * Descripcion[]) {
    struct Nodo * VNodo = (struct Nodo *) malloc(sizeof(struct Nodo));
    TareaIDs++;

    VNodo->T.TareaID = TareaIDs;
    VNodo->T.Descripcion = Descripcion;
    VNodo->T.Duracion = (rand() % (100 - 10 + 1)) + 10; // (rand() % (MAX - MIN + 1)) + MIN
    VNodo->Siguiente = NULL;

    return VNodo;
}

void InsertarNodo(struct Nodo ** Start, struct Nodo * VNodo) {
    VNodo->Siguiente = Start;
    *Start = VNodo;
}

void InsertarAlFinal(struct Nodo * Start, struct Nodo * VNodo) {
    struct Nodo * NodoAux = Start;

    while (NodoAux->Siguiente) {
        NodoAux = NodoAux->Siguiente;
    }

    NodoAux->Siguiente = VNodo;
}

struct Nodo * BuscarNodo(struct Nodo * Start, int IdBuscado) {
    struct Nodo * Aux = Start;

    while (Aux && Aux->T.TareaID != IdBuscado) {
        Aux = Aux->Siguiente;
    }

    return Aux;
}

struct Nodo * QuitarNodo(struct Nodo ** Start, int IdBuscado) {
    struct Nodo *NodoAux = *Start;
    struct Nodo *NodoAnt = NULL;

    while (NodoAux != NULL && NodoAnt->T.TareaID != IdBuscado) {
        NodoAnt = NodoAux;
        NodoAux = NodoAux->Siguiente;
    }

    if (NodoAux != NULL) {
        if (NodoAux == *Start) {
            *Start = NodoAux->Siguiente;
        } else {
            NodoAnt->Siguiente = NodoAux->Siguiente;
        }
        NodoAux->Siguiente = NULL;
    }

    return NodoAux;
}

void EliminarNodo(struct Nodo * VNodo) {
    if (VNodo) {
        if (VNodo->T.Descripcion) free(VNodo->T.Descripcion);
        free(VNodo);
    }
}