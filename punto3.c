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
    struct Nodo* sig;
}typedef Nodo;

Nodo * tareas;
Nodo * tareasRealizadas;

Nodo* crearListaVacia();
Nodo* crearNodo(item id);
Tarea crearTarea(item id);
void insertarNodo(Nodo **tareas, item id);
void moverTareas(Nodo **tareas, Nodo **tareasRealizadas);
void preguntarMostrar(Nodo *tareas, Nodo *tareasRealizadas);
void mostrarTareas(Nodo *tareas);
void buscarTareasId(Nodo *tareas, Nodo *tareasRealizadas);
void buscarTareasPalabra(Nodo *tareas, Nodo *tareasRealizadas);
void liberarMemoria(Nodo **tareas, Nodo **tareasRealizadas);

int main(){
    srand(time(NULL));
    int id = 0, aux = -1, aux2;

    do{
        printf("----------MENU---------\n");
        printf("1 - Agregar tarea\n2 - Marcar como REALIZADA\n3 - Mostrar lista de tareas\n4 - Buscar tarea ID\n5 - Buscar tarea PALABRA\n0 - Finalizar programa\n\nElija una opcion: ");
        fflush(stdin);
        scanf("%d", &aux);
        printf("-----------------------\n");

        switch (aux)
        {
        case 1:
            printf("Quiere crear una nueva tarea?\n1 - Si\n2 - No\nElija una opcion: ");
            fflush(stdin);
            scanf("%d", &aux2);

            if(aux2 == 1){
                id++;
                insertarNodo(&tareas, id);
            }
            break;
        
        case 2:
            moverTareas(&tareas, &tareasRealizadas);
            break;

        case 3:
            preguntarMostrar(tareas, tareasRealizadas);
            break;

        case 4:
            buscarTareasId(tareas, tareasRealizadas);
            break;

        case 5:
            buscarTareasPalabra(tareas, tareasRealizadas);
            break;
        
        default:
            liberarMemoria(&tareas, &tareasRealizadas);
            free(tareas);
            free(tareasRealizadas);
            printf("EL PROGRAMA FINALIZO");
            break;
        }
        

    }while(aux != 0);
    
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

void moverTareas(Nodo **tareas, Nodo **tareasRealizadas){
    int realizada;
    Nodo * aux = *tareas;
    Nodo * ant = NULL;
    printf("Datos de las tareas\n");
    while (aux != NULL){
        printf("ID de la tarea: %d\n", aux->T.tareaID);
        printf("Descripcion: ");
        puts(aux->T.desc);
        printf("Duracion: %d\n", aux->T.duracion);
        printf("Se realizo? 1-si, 0-no: ");
        fflush(stdin);
        scanf("%d", &realizada);
        if (realizada) {                                    //aqui
            if(ant == NULL){
                *tareas = aux->sig;
                
                aux->sig = *tareasRealizadas;
                *tareasRealizadas = aux;
                aux = *tareas;
            }else{
                ant->sig = aux->sig;

                aux->sig = *tareasRealizadas;
                *tareasRealizadas = aux;
                aux = ant->sig;
            }
        }else{
            ant = aux;
            aux = aux->sig;
        }
        printf("-----------------------\n");
    }
}

void preguntarMostrar(Nodo *tareas, Nodo *tareasRealizadas){
    int control;
    printf("Que lista de tarea quiere ver?\n1 - Pendientes\n2 - Realizadas\n");
    fflush(stdin);
    scanf("%d", &control);
    if (control == 1){
        printf("\n---Tareas Pendientes---\n");
        mostrarTareas(tareas);
    }else{
        printf("\n---Tareas Realizadas---\n");
        mostrarTareas(tareasRealizadas);
    }
}

void mostrarTareas(Nodo *tareas){
    while(tareas != NULL){
        printf("ID de la tarea: %d\n", tareas->T.tareaID);
        printf("Descripcion: ");
        puts(tareas->T.desc);
        printf("Duracion: %d\n", tareas->T.duracion);
        tareas = tareas->sig;
        printf("-----------------------\n");
    }
}

void buscarTareasId(Nodo *tareas, Nodo *tareasRealizadas){
    int id, aux = 0;
    printf("Ingrese el id de la tarea que quiere buscar: ");
    fflush(stdin);
    scanf("%d", &id);

    while(tareas != NULL){
        if ((tareas->T.tareaID == id)){
            printf("-------PENDIENTE-------\n");
            printf("ID de la tarea: %d\n", tareas->T.tareaID);
            printf("Descripcion: ");
            puts(tareas->T.desc);
            printf("Duracion: %d\n", tareas->T.duracion);
            aux = 1;
            break;
        }
        tareas = tareas->sig;
    }

    while(tareasRealizadas != NULL){
        if ((tareasRealizadas->T.tareaID == id)) {
            printf("-------REALIZADA-------\n");
            printf("ID de la tarea: %d\n", tareasRealizadas->T.tareaID);
            printf("Descripcion: ");
            puts(tareasRealizadas->T.desc);
            printf("Duracion: %d\n", tareasRealizadas->T.duracion);
            aux = 1;
            break;
        }
        tareasRealizadas = tareasRealizadas->sig;
    }

    if(aux == 0){
        printf("La tarea con la id %d no se encontro.\n", id);
    }
}

void buscarTareasPalabra(Nodo *tareas, Nodo *tareasRealizadas){
    char palabra[20];
    int aux = 0;
    printf("Ingrese palabra clave: ");
    fflush(stdin);
    gets(palabra);
    char resultado;
    char resultado2;
    
    while(tareas != NULL){
        if ((strstr(tareas->T.desc, palabra) != NULL)){
            printf("PENDIENTE\n");
            printf("ID de la tarea: %d\n", tareas->T.tareaID);
            printf("Descripcion: ");
            puts(tareas->T.desc);
            printf("Duracion: %d\n", tareas->T.duracion);
            aux = 1;
            break;
        }
        tareas = tareas->sig;
    }

    while(tareasRealizadas != NULL){
        if ((strstr(tareasRealizadas->T.desc, palabra) != NULL)) {
            printf("REALIZADA\n");
            printf("ID de la tarea: %d\n", tareasRealizadas->T.tareaID);
            printf("Descripcion: ");
            puts(tareasRealizadas->T.desc);
            printf("Duracion: %d\n", tareasRealizadas->T.duracion);
            aux = 1;
            break;
        }
        tareasRealizadas = tareasRealizadas->sig;
    }

    if(aux == 0){
        printf("No se encontro ninguna tarea con la palabra: ");
        gets(palabra);
    }
}

void liberarMemoria(Nodo **tareas, Nodo **tareasRealizadas){
    Nodo * aux = *tareas;
    Nodo * aux2 = *tareasRealizadas;

    while(aux != NULL){
        free(aux->T.desc);
        aux = aux->sig;
        free(aux);
    }

    while(aux2 != NULL){
        free(aux2->T.desc);
        aux2 = aux2->sig;
        free(aux2);
    }
}