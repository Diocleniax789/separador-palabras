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
void mostrar_clasificacion(struct pal*);

int main(){
    int cant_pal_res, palabras_cargadas = 0;
    char pal_res[40][15], *texto;
    struct pal *todas_las_palabras;
    struct pal *palabras_depuradas;

    cant_pal_res = carga_reserva(pal_res);
    if(cant_pal_res == 0){
        printf("\n X no se ha cargado nada, por lo tanto no se podrá continuar X \n");
    } else{
        system("cls");
        texto = carga_texto();
        todas_las_palabras = separa(texto, &palabras_cargadas);
        palabras_depuradas = depura(todas_las_palabras, &palabras_cargadas);
        clasifica(palabras_depuradas, pal_res, cant_pal_res);

        mostrar_clasificacion(palabras_depuradas);
    }

    return 0;
}

int carga_reserva(char pal_res[40][15]){
    int i, contador_palabras = 0;
    char palabra[15] = {0};

    for(i = 0; i < 40; i++){
        system("cls");
        printf("\n - Para finalizar con la carga, simplemente coloque '*' \n");
        printf("\n Palabra reservada nro %i \n", i + 1);
        printf("\n + Ingrese la palabra reservada: ");
        scanf("%s", palabra);
        if(strcmp(palabra, "*") == 0){
            break;
        } else{
            strcpy(pal_res[i], palabra);
            contador_palabras++;
            printf("\n *** Palabra reservada almacenada con éxito! *** \n");
        }
    }

    return contador_palabras;
}

char *carga_texto(){
    static char texto[1000];
    int i = 0;
    char caracter;

    printf("\n + Escriba su texto aquí abajo (Ctrl+D para finalizar): \n");
    while((caracter = getchar()) != EOF && i < 1000){
        texto[i++] = caracter;
    }
    texto[i] = '\0';

    printf("\n *** TEXTO CARGADO *** \n");
    system("pause");

    return texto;
}

struct pal *separa(char *texto, int *palabras_cargadas){
    static struct pal todas_las_palabras[500];
    char copia_texto[1000], *token, delim[] = " .,\n";
    int long_palabra;

    strcpy(copia_texto, texto);
    token = strtok(copia_texto, delim);
    while(token != NULL){
        long_palabra = strlen(token);
        if(long_palabra <= 25){
            strcpy(todas_las_palabras[*palabras_cargadas].palabra, token);
            (*palabras_cargadas)++;
        }
        token = strtok(NULL, delim);
    }

    return todas_las_palabras;
}

struct pal *depura(struct pal *todas_las_palabras, int *palabras_cargadas){
    static struct pal palabras_depuradas[500];
    int i, j, cantidad_pal_dep_guardadas = 0, es_repetida;

    for(i = 0; i < *palabras_cargadas; i++){
        es_repetida = 0;
        for(j = 0; j < cantidad_pal_dep_guardadas; j++){
            if(strcmp(todas_las_palabras[i].palabra, palabras_depuradas[j].palabra) == 0){
                es_repetida = 1;
                break;
            }
        }
        if(!es_repetida){
            strcpy(palabras_depuradas[cantidad_pal_dep_guardadas].palabra, todas_las_palabras[i].palabra);
            cantidad_pal_dep_guardadas++;
        }
    }

    strcpy(palabras_depuradas[cantidad_pal_dep_guardadas].palabra, "*****");
    return palabras_depuradas;
}

void clasifica(struct pal *palabras_depuradas, char pal_res[][15], int cant_pal_res){
    int i, j, flag, flag2;
    char palabra[25];

    for(i = 0; strcmp(palabras_depuradas[i].palabra, "*****") != 0; i++){
        strcpy(palabra, palabras_depuradas[i].palabra);
        flag = 0;

        for(j = 0; j < cant_pal_res; j++){
            if(strcmp(palabra, pal_res[j]) == 0){
                flag = 1;
                break;
            }
        }

        if(flag){
            strcpy(palabras_depuradas[i].tipo, "Palabra reservada");
        } else if(strlen(palabra) <= 8 && isalpha(palabra[0])){
            flag2 = 0;
            for(j = 1; j < strlen(palabra); j++){
                if(!isalnum(palabra[j]) && palabra[j] != '_'){
                    flag2 = 1;
                    break;
                }
            }
            strcpy(palabras_depuradas[i].tipo, flag2 ? "Otro" : "Identificador");
        } else{
            strcpy(palabras_depuradas[i].tipo, "Otro");
        }
    }
}

void mostrar_clasificacion(struct pal *palabras_depuradas){
    int i;

    printf("\n Clasificación de palabras según su tipo \n");
    printf(" ======================================= ");
    for(i = 0; strcmp(palabras_depuradas[i].palabra, "*****") != 0; i++){
        printf("\n + PALABRA: %s", palabras_depuradas[i].palabra);
        printf("\n + TIPO: %s", palabras_depuradas[i].tipo);
        printf("\n -------------------------------------------------- \n");
    }
}

