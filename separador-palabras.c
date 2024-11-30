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

