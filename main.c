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
    char* n_in = "frase.txt", *n_out = "arbol.txt", *cifrado_bin = "binario.txt",*compreso = "compreso.txt",
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
            FILE *outArbol  = fopen(n_out, "w");
            preOrden_PIMP(Arbol,outArbol);
            fclose(outArbol);

            Binarios = NULL;
            CrearTabla(Arbol,0,0,&Binarios,0);
            mostrarBinarios(Binarios);
            FILE *outBinario = fopen(cifrado_bin,"w");
            obetenerTiraBinaria(Binarios,letras,outBinario);
            fclose(outBinario);
            FILE *inBinario = fopen(cifrado_bin,"rt");
            char *tiraBinaria = "";
            if (inBinario == NULL) {
                puts("Este archivo no existe");
            }else {
                fgets(tiraBinaria, 1000, inBinario);
            }
            while(strlen(tiraBinaria)%8 != 0){
                sprintf(tiraBinaria, "%s0",tiraBinaria);
            }
            puts(tiraBinaria);
            int numeroEsp = strlen(tiraBinaria)/8;
            int *caracteres = (int*)malloc(numeroEsp* sizeof(int));
            int k = 0;
            for (int i = 0; i < numeroEsp ; ++i) {
                int decBin = 0;
                char arregloDeBytes[8];
                for (int j = 0; j < 8; ++j) {
                    arregloDeBytes[j] = tiraBinaria[k];
                    k++;
                }
                decBin = atoi(arregloDeBytes);
                decBin = decimal(decBin);
                caracteres[i] = decBin;
            }
            FILE *outCompreso = fopen(compreso,"w");
            for (int l = 0; l < numeroEsp ; ++l) {
                fprintf(outCompreso,"%c",caracteres[l]);
                printf("%d >> %c\n",caracteres[l],caracteres[l]);
            }
            fclose(outCompreso);
            break;
        case '2':
            break;
        default:
            puts("?OOO che?ol");
            break;
        case '0':
            puts("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAdios");
            break;
    }


    return 0;
}