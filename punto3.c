#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int item;

typedef struct Tarea{
    int tareaID;
    char *desc;
    int duracion;
}Tarea;

struct Nodo{
    Tarea T;
    Nodo *sig;
}typedef Nodo;

Nodo * tareas;
Nodo * tareasRealizadas;

Nodo* crearListaVacia();
Nodo* crearNodo(item id);
Tarea crearTarea(item id);
void insertarNodo(Nodo** tareas, item id);
void moverTareas(Nodo **tareas, Nodo **tareasRealizadas);
void preguntarMostrar(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas);
void mostrarTareas(Tarea **tareas, int cantTareas);
void buscarTareasId(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas);
void buscarTareasPalabra(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas);

int main(){
    srand(time(NULL));
    int id = 0, aux;

    printf("Quiere crear una nueva tarea?\n1 - Si\n2 - No\n");
    scanf("%d", &aux);

    if(aux == 1){
        id++;
        insertarNodo(&tareas, id);
    }
    
    return 0;
}

Nodo* crearListaVacia(){
    return NULL;
}

Nodo* crearNodo(item id){
    Nodo * nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->T = crearTarea(id);
    nuevo->sig = NULL;
    return nuevo;
}

Tarea crearTarea(item id){
    srand(time(NULL));
    Tarea t;
    printf("Ingrese los datos de la tarea %d\n", id);
    t.tareaID = id;
    t.desc = (char *)malloc(50 * sizeof(char));
    printf("Ingrese la desc: ");
    fflush(stdin);
    gets(t.desc);
    t.duracion = rand() % (100 - 10 + 1) + 10;
    return t;
}

void insertarNodo(Nodo** tareas, item id){
    Nodo * nuevo = crearNodo(id);
    nuevo->sig = *tareas;
    *tareas = nuevo;
}



void preguntarMostrar(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas){
    int control;
    printf("Que lista de tarea quiere ver?\n1 - Pendientes\n2 - Realizadas\n");
    scanf("%d", &control);
    if (control == 1){
        printf("Tareas Pendientes\n");
        mostrarTareas(tareas, cantTareas);
    }else{
        printf("Tareas Realizadas\n");
        mostrarTareas(tareasRealizadas, cantTareas);
    }
}

void mostrarTareas(Tarea **tareas, int cantTareas){
    for (int i = 0; i < cantTareas; i++){
        if (tareas[i] != NULL){
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
            printf("-----------------------\n");
        }
    }
}

void moverTareas(Nodo **tareas, Nodo **tareasRealizadas){
    Nodo * aux = *tareas;
    Nodo * aux2 = *tareasRealizadas;
    printf("Datos de las tareas\n");
    while (aux){
        int realizada;
        printf("ID de la tarea: %d\n", aux->T.tareaID);
        printf("Descripcion: ");
        puts(aux->T.desc);
        printf("Duracion: %d\n", aux->T.duracion);
        printf("Se realizo? 1-si, 0-no: ");
        scanf("%d", &realizada);
        if (realizada) {                                    //aqui
            tareasRealizadas[i] = tareas[i];
            tareas[i] = NULL;
        }
        printf("-----------------------\n");
    }
}

void buscarTareasId(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas){
    int id;
    printf("Ingrese el id de la tarea que quiere buscar: ");
    scanf("%d", &id);
    for (int i = 0; i < cantTareas; i++){
        if ((tareas[i] != NULL) && (tareas[i]->tareaID == id)){
            printf("PENDIENTE\n");
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
        }
        if ((tareasRealizadas[i]!=NULL) && (tareasRealizadas[i]->tareaID == id)) {
            printf("REALIZADA\n");
            printf("ID de la tarea: %d\n", tareasRealizadas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareasRealizadas[i]->desc);
            printf("Duracion: %d\n", tareasRealizadas[i]->duracion);
        }
    }
}

void buscarTareasPalabra(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas){
    char palabra[20];
    printf("Ingrese palabra clave: ");
    fflush(stdin);
    gets(palabra);
    char resultado;
    char resultado2;
    for (int i = 0; i < cantTareas; i++){
        
        if ((tareas[i] != NULL) && (strstr(tareas[i]->desc, palabra) != NULL)){
            printf("PENDIENTE\n");
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
        }
        if ((tareasRealizadas[i] != NULL) && (strstr(tareasRealizadas[i]->desc, palabra) != NULL)) {
            printf("REALIZADA\n");
            printf("ID de la tarea: %d\n", tareasRealizadas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareasRealizadas[i]->desc);
            printf("Duracion: %d\n", tareasRealizadas[i]->duracion);
        }
    }
}