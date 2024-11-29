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
struct pal * depura(char*,int*);
void clasifica(struct pal*,char pal_res[][15],int);

int main(){




    return 0;

}
