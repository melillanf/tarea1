#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

typedef struct Juego{
    char * nombre;
    char * marca;
    char** tipos;
    int minjugadores;
    int maxjugadores;
    char * juegobase;
}Juego;

List * creaListaJuegos(FILE * fp);

void * addJuego(List * lista, char * nombre, char * marca, int minjugadores, int maxjugadores, char * juegobase);//faltan los tipos

void buscCantJug(List * lista, int cantjug);

void buscMarca(List * lista, char * marca);

void buscNombre(List * lista, char * nombre);

void buscTipo(List* lista, char * tipo);

void buscTipoCant(List * lista, char * tipo, int cantjugadores);

void mostrarJuegos(List * list);

void mostrarExt(List * list);

int main()
{
    FILE * fp = fopen("50 juegos.csv", "r");
    List * lista = creaListaJuegos(fp);
    Juego * aux = first(lista);
    char * nombre = "Monopoly";
    buscNombre(lista,nombre);
    //while(aux!=NULL){
    //printf("%s , %s ,\n",aux->nombre, aux->marca);
    //aux = next(lista);
    //}
        //creaListaJuegos(juegos,fp);
    /*int p=0;
    int op;

    while(op < 11)
    {
        //printf("1.- Importar juegos\n");
        printf("2.- Exportar juegos\n");
        printf("3.- Agregar juegos\n");
        printf("4.- Buscar la cantidad de jugadores\n");
        printf("5.- Buscar juegos por marca\n");
        printf("6.- Buscar juegos por nombre\n");
        printf("7.- Buscar juegos por tipo\n");
        printf("8.- Buscar juegos por mas de un criterio\n");
        printf("9.- Mostrar todos los juegos\n");
        printf("10.- Mostrar extensiones\n");
        printf("Indica la opcion: ");
        scanf("%d", &op);


        switch(op)
        {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 7: break;
            case 8: break;
            case 9: break;
            case 10: break;
            case 11: break;
        }
    }*/
    return 0;
}
List * creaListaJuegos(FILE *fp){
    List * lista = createList();
    char * linea[1024];
     while (fgets (linea, 1023, fp) != NULL) {
        char * nombre = get_csv_field(linea, 0);

        char * marca = get_csv_field(linea, 1);

        //char ** tipo = get_csv_field(linea, 2);

        int minjugadores = atoi(get_csv_field(linea, 3));

        int maxjugadores = atoi(get_csv_field(linea, 4));

        char * juegobase = get_csv_field(linea, 5);

        addJuego(lista, nombre, marca, minjugadores, maxjugadores, juegobase);
     }
     return lista;
}

void * addJuego(List * lista, char * nombre, char * marca, int minjugadores, int maxjugadores, char * juegobase){
    Juego * nuevo = (Juego*)malloc(sizeof(Juego)); //reserva memoria
    nuevo->nombre = nombre; //asigna las variables al juego
    nuevo->marca = marca;
    //nuevo->tipos = tipos;
    nuevo->minjugadores = minjugadores;
    nuevo->maxjugadores = maxjugadores;
    nuevo->juegobase = juegobase;
    push_back(lista, nuevo);//se inserta al final de la lista
}

void buscCantJug(List * lista, int cantjug){
    Juego * aux= first(lista);
    do{
        if(aux->minjugadores<=cantjug && cantjug<=aux->maxjugadores){//compara la cant jugadores del juego con el numero de jugadores indicado
            printf("%s\n",aux->nombre);//imprime si coinciden las variables
        }
        aux = next(lista);
    }while(aux!= NULL);//avanza en la lista si no está al final de ella

}

void buscMarca(List * lista, char * marca){
    Juego * aux= first(lista);
    do{
        if(strcmp(aux->marca,marca)==0){//compara la marca con cada juego
            printf("%s\n",aux->nombre);//imprime en caso de coincidir
        }
        aux = next(lista);
    }while(aux!=NULL);//repite el bucle siempre que no sea el final de la lista
}

void buscNombre(List * lista, char * nombre){
    Juego * aux= first(lista);
    do{
        if(strcmp(aux->nombre,nombre)==0){
            printf("%s\n",aux->nombre);
        }
        aux = next(lista);
    }while(aux!= NULL);
}

/*void buscTipo(List * lista, char * tipo){
    Juego * aux = first(lista);
    do{
        if(strcmp(aux->tipos,tipo)==0){
            printf("%s",aux->nombre);
        }
        aux = next(lista);
    }while(aux!=NULL);
}
*/

/*void buscTipoCant(List * lista, char * tipo, int cantjugadores){
    Juego * aux;// auxiliar para apuntar al juego de la lista+
    aux = first(lista);
    do{
        if(strcmp(aux->tipos,tipo)==0 && (aux->minjugadores<=cantjugadores<=aux->maxjugadores)){
            printf("%s",aux->nombre);
           }
        aux = next(lista);
    }while(aux!=NULL);
}
*/

