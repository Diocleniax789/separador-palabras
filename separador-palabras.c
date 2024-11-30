#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct pal{
    char palabra[25];
    char tipo[20];
};

int carga_reserva(char[40][15]);
char * carga_texto(void);
struct pal * separa(char*,int*);
struct pal * depura(struct pal*,int*);
void clasifica(struct pal*,char pal_res[][15],int);

int main(){
    int cant_pal_res,palabras_cargadas = 0;
    char pal_res[40][15],*texto;
    struct pal * todas_las_palabras;
    struct pal * palabras_depuradas;

    cant_pal_res = carga_reserva(pal_res);
    texto = carga_texto();
    todas_las_palabras = separa(texto,&palabras_cargadas);
    palabras_depuradas = depura(todas_las_palabras,palabras_cargadas);
    clasifica(palabras_depuradas,pal_res,cant_pal_res);

    return 0;
}

int carga_reserva(char pal_res[40][15]){
    int i,contador_palabras = 0;
    char palabra[15] = {0};

    for(i = 0; i < 40; i++){
        system("cls");
        fflush(stdin);
        printf("\n - Para finalizar con la carga, simplemente coloque '*' \n");
        printf("\n");
        printf("\n Palabra reserveda nro %i \n".i + 1);
        printf("\n");
        printf("\n + Ingrese la palabra reservada: ");
        scanf("%s",palabra);
        if(strcmp(palabra,"*") == 0){
            break;
        } else{
            strcpy(pal_res[i],palabra);
            contador_palabras++;
            printf("\n *** Palabra reservada almacenada con exito! *** \n");
            printf("\n");
            system("cls");
        }
    }

    printf("\n *** SE HAN CARGADO TODAS LAS PALABRAS RESERVADAS CON EXITO! *** \n");
}

