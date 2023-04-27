#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea{
    int tareaID;
    char *desc;
    int duracion;
}Tarea;

int pedirNumTareas();
void preguntarMostrar(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas);
void mostrarTareas(Tarea **tareas, int cantTareas);
void moverTareas(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas);
void BuscaTareaPorId(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas);
void BuscaTareaPorPalabra(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas);

int main(){
    int numTareas;
    numTareas = pedirNumTareas();
    srand(time(NULL));
    Tarea **tareas = (Tarea **)malloc(numTareas * sizeof(Tarea *));
    Tarea **tareasRealizadas = (Tarea **)malloc(numTareas * sizeof(Tarea *));

    for (int i = 0; i < numTareas; i++) {
        tareasRealizadas[i] = NULL;
        tareas[i] = NULL;
    }

    for (int i = 0; i < numTareas; i++){
        tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        printf("Ingrese los datos de la tarea %d\n", i + 1);
        tareas[i]->tareaID = i + 1;
        tareas[i]->desc = (char *)malloc(50 * sizeof(char));
        printf("Ingrese la desc: ");
        fflush(stdin);
        gets(tareas[i]->desc);
        tareas[i]->duracion = rand() % (100 - 10 + 1) + 10;
    }
    moverTareas(tareas,tareasRealizadas, numTareas);
    preguntarMostrar(tareas, tareasRealizadas, numTareas);
    buscarTareasPalabra(tareas, tareasRealizadas, numTareas);
    return 0;
}

int pedirNumTareas(){
    int num;
    printf("Igrese el numero de tareas: ");
    scanf("%d", &num);
    return num;
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
        }
        printf("-----------------------\n");
    }
}

void moverTareas(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas){
    printf("Datos de las tareas\n");
    for (int i = 0; i < cantTareas; i++){
        int realizada;
        printf("ID de la tarea: %d\n", tareas[i]->tareaID);
        printf("Descripcion: ");
        puts(tareas[i]->desc);
        printf("Duracion: %d\n", tareas[i]->duracion);
        printf("Se realizo? 1-si, 0-no: ");
        scanf("%d", &realizada);
        if (realizada) {
            tareasRealizadas[i] = tareas[i];
            tareas[i] = NULL;
        }
        printf("-----------------------\n");
    }
}

void BuscaTareaPorId(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas){
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

void BuscaTareaPorPalabra(Tarea **tareas, Tarea **tareasRealizadas, int cantTareas){
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