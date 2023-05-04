#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
Nodo * tareasProceso;

Nodo* crearListaVacia();
Nodo* crearNodo(int id);
Tarea crearTarea(int id);

void insertarNodo(Nodo **tareas, int id);
void moverTareas(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasProceso);
void preguntarMostrar(Nodo *tareas, Nodo *tareasRealizadas, Nodo *tareasProceso, int num);
void mostrarTareas(Nodo *tareas);
void buscarTareasId(Nodo *tareas, Nodo *tareasRealizadas, Nodo *tareasProceso);
void seleccionarTareasId(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasProceso, int seleccionada);
void buscarTareasPalabra(Nodo *tareas, Nodo *tareasRealizadas, Nodo *tareasProceso);
void liberarMemoria(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasProceso);
void eliminar(Nodo **tareas, int id);
void mostrarDatos(Nodo *tareas);

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
            moverTareas(&tareas, &tareasRealizadas, &tareasProceso);
            break;

        case 3:
            preguntarMostrar(tareas, tareasRealizadas, tareasProceso, 0);
            break;

        case 4:
            buscarTareasId(tareas, tareasRealizadas, tareasProceso);
            break;

        case 5:
            buscarTareasPalabra(tareas, tareasRealizadas, tareasProceso);
            break;
        
        default:
            liberarMemoria(&tareas, &tareasRealizadas, &tareasProceso);
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

Nodo* crearNodo(int id){
    Nodo * nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->T = crearTarea(id);
    nuevo->sig = NULL;
    return nuevo;
}

Tarea crearTarea(int id){
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

void insertarNodo(Nodo** tareas, int id){
    Nodo * nuevo = crearNodo(id);
    nuevo->sig = *tareas;
    *tareas = nuevo;
}

void moverTareas(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasProceso){
    int control, seleccionada;
    
    do{
        printf("Datos de las tareas\n");
        preguntarMostrar(*tareas, *tareasRealizadas, *tareasProceso, 4);
        
        printf("Seleccione una tarea (id): ");
        fflush(stdin);
        scanf("%d", &seleccionada);
        seleccionarTareasId(tareas, tareasRealizadas, tareasProceso, seleccionada);
        
        printf("Quiere gestionar otra tarea?\n1 - Si\n0 - No\nOpcion: ");
        fflush(stdin);
        scanf("%d", &control);
    }while(control != 0);
    preguntarMostrar(*tareas, *tareasRealizadas, *tareasProceso, 1);
    mostrarDatos(*tareas);
    preguntarMostrar(*tareas, *tareasRealizadas, *tareasProceso, 2);
    mostrarDatos(*tareasRealizadas);
    preguntarMostrar(*tareas, *tareasRealizadas, *tareasProceso, 3);
    mostrarDatos(*tareasProceso);
    
}

void seleccionarTareasId(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasProceso, int seleccionada){
    int aux = 0;
    int control;
    Nodo * aux1 = *tareas;
    Nodo * aux2 = *tareasRealizadas;
    Nodo * aux3 = *tareasProceso;
    Nodo * ant1 = NULL;
    Nodo * ant2 = NULL;
    Nodo * ant3 = NULL;

    while(aux1 != NULL){
        if ((aux1->T.tareaID == seleccionada)){
            aux = 1;
            break;
        }
        ant1 = aux1;
        aux1 = aux1->sig;
    }

    while(aux2 != NULL){
        if ((aux2->T.tareaID == seleccionada)) {
            aux = 2;
            break;
        }
        ant2 = aux2;
        aux2 = aux2->sig;
    }

    while(aux3 != NULL){
        if ((aux3->T.tareaID == seleccionada)) {
            aux = 3;
            break;
        }
        ant3 = aux3;
        aux3 = aux3->sig;
    }

    if(aux == 0){
        printf("La tarea con la id %d no se encontro.\n", seleccionada);
    }else{
        switch (aux){
        case 1:
            printf("Seleccione una opcion\n1 - Mover a REALIZADAS\n2 - Mover a EN PROCESO\n3 - Eliminar\n4 - Nada\n");
            fflush(stdin);
            scanf("%d", &control);

            switch (control){
            case 1:
                if(ant1 == NULL){
                    *tareas = aux1->sig;
                    
                    aux1->sig = *tareasRealizadas;
                    *tareasRealizadas = aux1;
                }else{
                    ant1->sig = aux1->sig;

                    aux1->sig = *tareasRealizadas;
                    *tareasRealizadas = aux1;
                }
                break;
            case 2:
                if(ant1 == NULL){
                    *tareas = aux1->sig;
                    
                    aux1->sig = *tareasProceso;
                    *tareasProceso = aux1;
                }else{
                    ant1->sig = aux1->sig;

                    aux1->sig = *tareasProceso;
                    *tareasProceso = aux1;
                }
                break;
            case 3:
                eliminar(tareas, seleccionada);
                break;
            default:
                break;
            }
            break;
        case 2:
            printf("Seleccione una opcion\n1 - Mover a PENDIENTE\n2 - Mover a EN PROCESO\n3 - Eliminar\n4 - Nada\n");
            fflush(stdin);
            scanf("%d", &control);

            switch (control){
            case 1:
                if(ant2 == NULL){
                    *tareasRealizadas = aux2->sig;
                    
                    aux2->sig = *tareas;
                    *tareas = aux2;
                }else{
                    ant2->sig = aux2->sig;

                    aux2->sig = *tareas;
                    *tareas = aux2;
                }
                break;
            case 2:
                if(ant1 == NULL){
                    *tareasRealizadas = aux2->sig;
                    
                    aux2->sig = *tareasProceso;
                    *tareasProceso = aux2;
                }else{
                    ant2->sig = aux2->sig;

                    aux2->sig = *tareasProceso;
                    *tareasProceso = aux2;
                }
                break;
            case 3:
                eliminar(tareasRealizadas, seleccionada);
                break;
            default:
                break;
            }
            break;
        case 3:
            printf("Seleccione una opcion\n1 - Mover a REALIZADAS\n2 - Mover a PENDIENTE\n3 - Eliminar\n4 - Nada\n");
            fflush(stdin);
            scanf("%d", &control);

            switch (control){
            case 1:
                if(ant3 == NULL){
                    *tareasProceso = aux3->sig;
                    
                    aux3->sig = *tareasRealizadas;
                    *tareasRealizadas = aux3;
                }else{
                    ant3->sig = aux3->sig;

                    aux3->sig = *tareasRealizadas;
                    *tareasRealizadas = aux3;
                }
                break;
            case 2:
                if(ant3 == NULL){
                    *tareasProceso = aux3->sig;
                    
                    aux3->sig = *tareas;
                    *tareas = aux3;
                }else{
                    ant3->sig = aux3->sig;

                    aux3->sig = *tareas;
                    *tareas = aux3;
                }
                break;
            case 3:
                eliminar(tareasProceso, seleccionada);
                break;
            default:
                break;
            }
            break;
        
        default:
            break;
        }
    }
}

void preguntarMostrar(Nodo *tareas, Nodo *tareasRealizadas, Nodo *tareasProceso, int num){
    int control;
    if(num == 0){
        printf("Que lista de tarea quiere ver?\n1 - Pendientes\n2 - Realizadas\n3 - En proceso\nOpcion: ");
        fflush(stdin);
        scanf("%d", &control);
    }else{
        control = num;
    }

    switch (control){
    case 1:
        printf("\n---Tareas Pendientes---\n");
        mostrarTareas(tareas);
        break;
    case 2:
        printf("\n---Tareas Realizadas---\n");
        mostrarTareas(tareasRealizadas);
        break;
    case 3:
        printf("\n---Tareas en Proceso---\n");
        mostrarTareas(tareasProceso);
        break;
    case 4:
        printf("\n---Tareas Pendientes---\n");
        mostrarTareas(tareas);
        printf("\n---Tareas Realizadas---\n");
        mostrarTareas(tareasRealizadas);
        printf("\n---Tareas en Proceso---\n");
        mostrarTareas(tareasProceso);
        break;
    default:
        break;
    }
}

void mostrarTareas(Nodo *tareas){
    if(tareas != NULL){
        while(tareas != NULL){
            printf("ID de la tarea: %d\n", tareas->T.tareaID);
            printf("Descripcion: ");
            puts(tareas->T.desc);
            printf("Duracion: %d\n", tareas->T.duracion);
            tareas = tareas->sig;
            printf("-----------------------\n");
        }
    }else{
        printf("La lista de tareas esta vacia\n");
    }
}

void buscarTareasId(Nodo *tareas, Nodo *tareasRealizadas, Nodo *tareasProceso){
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

    while(tareasProceso != NULL){
        if ((tareasProceso->T.tareaID == id)) {
            printf("-------PROCESO-------\n");
            printf("ID de la tarea: %d\n", tareasProceso->T.tareaID);
            printf("Descripcion: ");
            puts(tareasProceso->T.desc);
            printf("Duracion: %d\n", tareasProceso->T.duracion);
            aux = 1;
            break;
        }
        tareasProceso = tareasProceso->sig;
    }

    if(aux == 0){
        printf("La tarea con la id %d no se encontro.\n", id);
    }
}

void buscarTareasPalabra(Nodo *tareas, Nodo *tareasRealizadas, Nodo *tareasProceso){
    char palabra[20];
    int aux = 0;
    printf("Ingrese palabra clave: ");
    fflush(stdin);
    gets(palabra);
    
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

    while(tareasProceso != NULL){
        if ((strstr(tareasProceso->T.desc, palabra) != NULL)) {
            printf("REALIZADA\n");
            printf("ID de la tarea: %d\n", tareasProceso->T.tareaID);
            printf("Descripcion: ");
            puts(tareasProceso->T.desc);
            printf("Duracion: %d\n", tareasProceso->T.duracion);
            aux = 1;
            break;
        }
        tareasProceso = tareasProceso->sig;
    }

    if(aux == 0){
        printf("No se encontro ninguna tarea con esta palabra\n");
    }
}

void liberarMemoria(Nodo **tareas, Nodo **tareasRealizadas, Nodo **tareasProceso){
    Nodo * aux = *tareas;
    Nodo * aux2 = *tareasRealizadas;
    Nodo * aux3 = *tareasProceso;

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

    while(aux3 != NULL){
        free(aux3->T.desc);
        aux3 = aux3->sig;
        free(aux3);
    }
}

void eliminar(Nodo **tareas, int id){
    Nodo * aux = *tareas;
    Nodo * ant = NULL;

    while(aux != NULL){
        if(aux->T.tareaID == id){
            if(ant == NULL){
                *tareas = aux->sig;
                free(aux->T.desc);
                free(aux);
                aux = *tareas;
                *tareas = aux;
            }else{
                ant->sig = aux->sig;
                free(aux->T.desc);
                free(aux);
                aux = ant->sig;
            }
        }else{
            ant = aux;
            aux = aux->sig;
        }
    }
}

void mostrarDatos(Nodo *tareas){
    int cont = 0, tiempo = 0;
    while (tareas != NULL){
        cont++;
        tiempo += tareas->T.duracion;
        tareas = tareas->sig;
    }
    if(cont == 0){
        printf("La lista esta vacia\n");
    }else{
        printf("Cantidad de tareas: %d\nTiempo total: %d\n", cont, tiempo);
    }
}