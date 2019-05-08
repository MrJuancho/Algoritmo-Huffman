#include <stdio.h>
#include <ctype.h>
#include "funciones.h"

int main() {
    char principal;
    char abcdario[29] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z','.',',','#'};
    int conteos[29] = {0};
    Nodo *lista_frec = NULL, *arbolitos, *Arbol;
    NodoBin *Binarios;
    char* n_in = "frase.txt", *n_out = "arbol.txt", *cifrado_bin = "binario.txt",*compreso = "compreso.bin",
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
    int length = Mostrar_Datos(lista_frec);

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
            FILE *outCompreso = fopen(compreso,"wb");
            fwrite(&numeroEsp, sizeof(int), 1, outCompreso);
            for (int l = 0; l < numeroEsp ; ++l) {
                fprintf(outCompreso,"%c",caracteres[l]);
                printf("%d >> %c\n",caracteres[l],caracteres[l]);
            }
            fclose(outCompreso);
            break;
        case '2':
            char arbol_des[100], compreso_des[100], *salida = "frasedec.txt";
            puts("Ingresa el nombre de el archivo del arbol:");
            scanf("%s",arbol_des);
            fflush(stdin);
            puts("Ingresa el nombre del archivo del cifrado:");
            scanf(" %s",compreso_des);
            fflush(stdin);
            FILE *in_arbol,*in_compreso,*salida_txt;
            in_arbol = fopen(arbol_des,"r");
            in_compreso = fopen(compreso_des,"rb");
            Nodo *listaaux = NULL, *Arbol_dec = NULL;
            int nElementos = 0,i = 0,j = 0,auxmil;
            int* numeros = (int*)malloc(nElementos* sizeof(int));
            if (in_arbol == NULL && in_compreso == NULL) {
                puts("Este archivo no existe");
                return 0;
            }else{
                fread(&nElementos, sizeof(int), 1, in_compreso);
                for (int l = 0; l < nElementos ; ++l) {
                    int temp = 0;
                    fread(&temp, sizeof(char), 1, in_compreso);
                    numeros[l] = temp;
                }
            }
            printf("%d\n",nElementos);
            char arreglo[500];
            FILE *bin_dec = fopen("bin_dec.txt","w+");
            for (int m = 0; m < nElementos ; ++m) {
                int temp = binario(numeros[m]);
                char *arrtemp = "";
                sprintf(arrtemp,"%08d",temp);
                fprintf(bin_dec,"%s",arrtemp);
            }
            rewind(bin_dec);
            fgets(arreglo,500,bin_dec);
            puts(arreglo);
            while ((auxmil = fgetc(in_arbol)) != EOF) {
                if (auxmil == ' ')
                    i++;
            }
            i /= 2;
            int *num = (int*) malloc(i*sizeof(int));
            char *letter = (char*) malloc(i*sizeof(char));
            rewind(in_arbol);
            while (!feof(in_arbol)) {
                fscanf(in_arbol, "%d %c ", &num[j], &letter[j]);
                if(letter[j] != '@') {
                    listaaux = Alta_Inicial(letter[j], num[j], listaaux);
                }
                j++;
            }
            listaaux = OrdenamientoSeleccion(listaaux);
            int size = Mostrar_Datos(listaaux);
            //Arbol_dec = constructTree(letter,num,size);
            //preOrden(Arbol_dec);

            //decode_file(Arbol_dec,arreglo);

            fclose(in_compreso);
            fclose(in_arbol);
            fclose(bin_dec);
            //fclose(salida_txt);
            break;
        default:
            puts("?OOO che?ol");
            break;
        case '0':
            puts("Adios");
            break;
    }
    return 0;
}