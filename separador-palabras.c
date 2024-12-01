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
    int cant_pal_res,palabras_cargadas = 0;
    char pal_res[40][15],*texto;
    struct pal * todas_las_palabras;
    struct pal * palabras_depuradas;

    cant_pal_res = carga_reserva(pal_res);
    if(cant_pal_res == 0){
        printf("\n");
        printf("\n X no se ha cargado nada, por lo tanto no se podra continuar X \n");
    } else{
        system("cls");
        texto = carga_texto();
        todas_las_palabras = separa(texto,&palabras_cargadas);
        palabras_depuradas = depura(todas_las_palabras,&palabras_cargadas);
        clasifica(palabras_depuradas,pal_res,cant_pal_res);

        mostrar_clasificacion(palabras_depuradas);

    }

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
        printf("\n Palabra reserveda nro %i \n",i + 1);
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

    if(contador_palabras == 0){
        printf("\n");
        printf("\n xxx NO SE HA CARGADO NADA! xxx\n");
    } else{
        printf("\n");
        printf("\n *** SE HAN CARGADO TODAS LAS PALABRAS RESERVADAS CON EXITO! *** \n");
    }

    return contador_palabras;
}

char * carga_texto(){
    char caracter;
    static char texto[1000];
    int i = 0;

    printf("\n + Escriba su texto aqui abajo: \n");
    while((caracter = getchar()) != EOF && i < 1000){
        texto[i] = caracter;
        i++;
    }

    texto[i] = '\0';

    printf("\n *** TEXTO CARGADO *** \n");
    printf("\n");
    system("pause");

    return texto;
}

struct pal * separa(char *texto, int *palabras_cargadas){
    static struct pal todas_las_palabras[500];
    char copia_texto[1000] = {0}, *token, delim[] = " .";
    int long_palabra;

    strcpy(copia_texto,texto);
    token = strtok(copia_texto,delim);
    while(token != NULL){
        long_palabra = strlen(token);
        if(long_palabra <=  25){
            strcpy(todas_las_palabras[*palabras_cargadas].palabra,token);
            palabras_cargadas++;
        }

        token = strtok(NULL,delim);
    }

    printf("\n *** TODO EL TEXTO FUE SEPARADO POR PALABRAS Y AGREGADOS A LA TABLA *** \n");
    printf("\n");
    system("cls");

    return todas_las_palabras;
}

struct pal * depura(struct pal *todas_las_palabras, int* palabras_cargadas){
  static struct pal palabras_depuradas[500];
  int i,j,pos = 0,flag = 0,cantidad_pal_dep_guardadas = 0;
  char palabra[25];

  j = 0;
  for(i = 0; i < cantidad_pal_dep_guardadas; i++){
    if(i == 0){
        strcpy(palabras_depuradas[cantidad_pal_dep_guardadas].palabra,todas_las_palabras[0].palabra);
        cantidad_pal_dep_guardadas++;
    } else{

        strcpy(palabra,todas_las_palabras[j].palabra);

        do{

          if(strcmp(palabra,todas_las_palabras[pos].palabra) == 0){
            flag = 1;
            break;
          } else{
            pos++;
          }

        } while(pos < cantidad_pal_dep_guardadas && flag == 1);

        if(flag == 1){
            printf("\n Palabra ya guardada en la tabla de depuradas \n");
        } else{
            strcpy(palabras_depuradas[cantidad_pal_dep_guardadas].palabra,palabra);
            cantidad_pal_dep_guardadas++;
        }
    }
  }

  strcpy(palabras_depuradas[cantidad_pal_dep_guardadas].palabra,"*****");

  return palabras_depuradas;
}

void clasifica(struct pal *palabras_depuradas,char pal_res[][15],int cant_pal_res){
    int i,pos = 0,flag = 0,long_pal,j,flag2;
    char palabra[25];

    for(i = 0; i < strcmp(palabras_depuradas[i].palabra,"*****") != 0; i++){
        strcpy(palabra,palabras_depuradas[i].palabra);
        do{
            if(strcmp(palabra,pal_res[pos]) == 0){
                flag = 1;
                break;
            } else{
                pos++;
            }
        } while(pos < cant_pal_res && flag == 1);

        if(flag == 1){
            strcpy(palabras_depuradas[i].tipo,"Palabra reservada");
        } else{
            long_pal = strlen(palabra);
            if(long_pal <= 8 && isalpha(palabra[0]) != 0){
                flag2 = 0;
                for(j = 1; j < long_pal; j++){
                    if(isalnum(palabra[j] != 0 && palabra[j] == '_')){
                        continue;
                    } else{
                        flag2 = 1;
                        break;
                    }
                }

                if(flag2 == 0){
                    strcpy(palabras_depuradas[i].tipo,"Identificador");
                } else{
                    strcpy(palabras_depuradas[i].tipo,"Otro");
                }

            } else{
                strcpy(palabras_depuradas[i].tipo,"Otro");

            }
        }
    }
}

void mostrar_clasificacion(struct pal *palabras_depuradas){
    int i;

    printf("\n Clasificacion de palabras segun su tipo \n");
    printf("\n ======================================= ");
    for(i = 0; strcmp(palabras_depuradas[i].palabra,"*****") != 0; i++){
        printf("\n + PALABRA: %s",palabras_depuradas[i].palabra);
        printf("\n + TIPO: %s",palabras_depuradas[i].tipo);
        printf("\n -------------------------------------------------- \n");
    }
}
