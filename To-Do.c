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
struct Nodo * CrearNodo(char * Descripcion, int Duracion);
void InsertarNodo(struct Nodo ** Start, struct Nodo * VNodo);
void InsertarAlFinal(struct Nodo * Start, struct Nodo * VNodo);
struct Nodo * BuscarNodo(struct Nodo * Start, int IdBuscado);
struct Nodo * QuitarNodo(struct Nodo ** Start, int IdBuscado);
void EliminarNodo(struct Nodo * VNodo);
void EliminarListaNodo(struct Nodo * Start);
void MostrarListaNodo(struct Nodo * Start);


int main() {
    struct Nodo *TareasPendientes = NULL;
    struct Nodo *TareasRealizadas = NULL;
    struct Nodo *NodoAux = NULL;
    char Buff[128];
    int Duracion = 0;
    int ID = 0;
    int Continuar = 1;

    srand(time(NULL)); // Empezar con una semilla distinta para el generador de numeros aleatoreo

    while (Continuar) {
        printf("Ingrese descripcion de Tarea: ");
        fflush(stdin); // Limpiar el buffer de la consola
        fgets(Buff, sizeof(Buff), stdin);
        Buff[strcspn(Buff, "\n")] = 0; // Pasen como quitar el \n del final :pray:

        do {
            printf("Ingrese Duracion de tarea: ");
            fflush(stdin); // Limpiar el buffer de la consola
            scanf("%d", &Duracion);

            if (Duracion < 10 || Duracion > 100) printf("Fuera de rango de duracion, intente de nuevo.\n\n");
        } while (Duracion < 10 || Duracion > 100);

        InsertarNodo(&TareasPendientes, CrearNodo(Buff, Duracion));

        printf("Quieres ingresar otra Tarea? (1 = SI / 0 = NO): ");
        fflush(stdin); // Limpiar el buffer de la consola
        scanf("%d", &Continuar);
        if (Continuar) printf("\n");
    }

    // Mostrar Tareas
    printf("\n=== Tareas Pendientes ===\n");
    MostrarListaNodo(TareasPendientes);
    printf("\n=== Tareas Pendientes ===\n");
    MostrarListaNodo(TareasRealizadas);

    Continuar = 1;
    while (Continuar) {
        printf("\nIngrese ID de la tarea Realizada: ");
        fflush(stdin); // Limpiar el buffer de la consola
        scanf("%d", &ID);

        NodoAux = QuitarNodo(&TareasPendientes, ID);
        if (NodoAux) {
            InsertarNodo(&TareasRealizadas, NodoAux);
            printf("Se inserto la Tarea %d en la lista de Realizados\n", ID);
        } else {
            printf("No se encontro la Tarea con ID: %d\n", ID);
        }

        printf("Quieres marcar otra Tarea realizada? (1 = SI / 0 = NO): ");
        fflush(stdin); // Limpiar el buffer de la consola
        scanf("%d", &Continuar);
    }

    // Mostrar Tareas
    printf("\n=== Tareas Pendientes ===\n");
    MostrarListaNodo(TareasPendientes);
    printf("\n=== Tareas Pendientes ===\n");
    MostrarListaNodo(TareasRealizadas);

    // Liberar Memoria
    EliminarListaNodo(TareasPendientes);
    EliminarListaNodo(TareasRealizadas);

    return 0;
}


struct Nodo * CrearNodo(char * Descripcion, int Duracion) {
    struct Nodo * VNodo = (struct Nodo *) malloc(sizeof(struct Nodo));

    VNodo->T.TareaID = TareaIDs;
    VNodo->T.Descripcion = (char *) malloc(sizeof(char) * (strlen(Descripcion) + 1));
    strcpy(VNodo->T.Descripcion, Descripcion);
    VNodo->T.Duracion = Duracion;
    VNodo->Siguiente = NULL;

    TareaIDs++;

    return VNodo;
}

void InsertarNodo(struct Nodo ** Start, struct Nodo * VNodo) {
    VNodo->Siguiente = *Start;
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

    while (NodoAux != NULL && NodoAux->T.TareaID != IdBuscado) {
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

void EliminarListaNodo(struct Nodo * Start) {
    struct Nodo *NodoAux = Start;
    struct Nodo *NodoAnt = NULL;

    while (NodoAux) {
        NodoAnt = NodoAux;
        NodoAux = NodoAux->Siguiente;

        EliminarNodo(NodoAnt);
    }
}

void MostrarListaNodo(struct Nodo * Start) {
    struct Nodo *NodoAux = Start;

    if (NodoAux) {
        while (NodoAux) {
            printf("ID: %d\tDuracion: %d\tDesc: %s\n",
                NodoAux->T.TareaID,
                NodoAux->T.Duracion,
                NodoAux->T.Descripcion
            );

            NodoAux = NodoAux->Siguiente;
        }
    } else {
        printf("Lista vacia\n");
    }
}