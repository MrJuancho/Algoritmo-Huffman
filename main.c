#include <stdio.h>
#include <ctype.h>
#include "funciones.h"

int main() {
    char principal;
    char abcdario[29] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z','.',',','#'};
    int conteos[29] = {0};
    Nodo *lista_frec = NULL, *arbolitos, *Arbol;
    NodoBin *Binarios, *aux;
    char* n_in = "frase.txt", *n_out = "arbol.txt", *cifrado_bin = "binario.txt",
    letras[100];
    FILE *archivo = fopen(n_in, "rt");
    if (archivo == NULL) {
        puts("Este archivo no existe");
        exit(-1);
    }else {
        fgets(letras, 100, archivo);
    }
    Formatear_texto(letras);
    puts(letras);
    Contar_Frecuancias(letras,conteos);
    for (int i = 0; i < 29 ; ++i) {
        if(conteos[i] != 0) lista_frec = Alta_Inicial(abcdario[i], conteos[i], lista_frec);
    }
    lista_frec = OrdenamientoSeleccion(lista_frec);
    Mostrar_Datos(lista_frec);

    puts("1 >> Codificar\n"
         "2 >> Decodificar\n"
         "0 >> Salir.\n");
    scanf("%c",&principal);
    fflush(stdin);
    switch (principal) {
        case '1':
            Arbol = lista_frec;
            while(Arbol && Arbol->sig){
                arbolitos = (Nodo *)malloc(sizeof(Nodo));
                arbolitos->dato = '@';
                arbolitos->L = Arbol;
                Arbol = Arbol->sig;
                arbolitos->R = Arbol;
                Arbol = Arbol->sig;
                arbolitos->frec = arbolitos->L->frec + arbolitos->R->frec;
                InsertarOrden(&Arbol, arbolitos);
            }
            preOrden(Arbol);
            FILE *out  = fopen(n_out, "w");
            preOrden_PIMP(Arbol,out);
            fclose(out);

            Binarios = NULL;
            CrearTabla(Arbol,0,0,&Binarios);
            FILE *out2 = fopen(cifrado_bin,"w");
            guardarBinarios(Binarios,out2,letras);
            fclose(out2);
            FILE *sacarBin = fopen(cifrado_bin,"r");
            char textobinario[200];
            if (sacarBin == NULL) {
                puts("Este archivo no existe");
                exit(-1);
            }else {
                fgets(textobinario, 200, sacarBin);
            }
            puts(textobinario);
            break;
        case '2':
            break;
        default:
            puts("?OOO che?ol");
            break;
        case '0':
            puts("Pinche practica fea osiosi");
            break;
    }


    return 0;
}