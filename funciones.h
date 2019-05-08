//
// Created by MrJuancho on 11/04/2019.
//

#ifndef ALGORITMO_HUFFMAN_FUNCIONES_H
#define ALGORITMO_HUFFMAN_FUNCIONES_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Nodo{
    char dato;
    int frec;

    struct _Nodo *sig;
    struct _Nodo *L;
    struct _Nodo *R;
}Nodo;

typedef struct _NodoBin{
    char letra;
    long int bits;
    char nbits;
    int binary;

    struct _NodoBin *sig;
}NodoBin;

Nodo* allocateMem(char dato, int frec){
    Nodo* dummy;
    dummy = (Nodo*)malloc(sizeof(Nodo));
    dummy -> dato = dato;
    dummy -> frec = frec;
    dummy -> sig = NULL;
    dummy -> R = NULL;
    dummy -> L = NULL;
    return dummy;
}

NodoBin* allocateMemBin(char letra, long int bits, char nbits,int binary){
    NodoBin* dummy;
    dummy = (NodoBin*)malloc(sizeof(NodoBin));
    dummy -> letra = letra;
    dummy -> bits = bits;
    dummy -> nbits = nbits;
    dummy ->binary = binary;
    dummy -> sig = NULL;
    return dummy;
}

void InsertarTabla(NodoBin** Tabla,char caracter,long int altura, int valor,int binario){
    NodoBin *auxiliar, *auxiliar_ref, *auxiliar_asignacion;
    auxiliar = allocateMemBin(caracter,valor,altura,binario);
    if(!*Tabla){
        *Tabla = auxiliar;
        (*Tabla)->sig = NULL;
    }else {
        auxiliar_ref = *Tabla;
        auxiliar_asignacion = NULL;
            while (auxiliar_ref && auxiliar_ref->letra < auxiliar->letra) {
                auxiliar_asignacion = auxiliar_ref;
                auxiliar_ref = auxiliar_ref->sig;
            }
        auxiliar->sig = auxiliar_ref;
        if (auxiliar_asignacion) {
            auxiliar_asignacion->sig = auxiliar;
        }else{
            *Tabla = auxiliar;
        }
    }
}

int binario (int n) {
    if (n == 0) {
        return n;
    } else {
        return binario(n / 2) * 10 + n % 2;
    }
}

int decimal(int n){
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0){
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

void CrearTabla(Nodo *arbol, int altura, int decimal_binario, NodoBin **tabla,int binarios)
{
    if(arbol->R) {
       // printf("R >> %d, %c\n", arbol->frec , arbol->dato);
        CrearTabla(arbol->R, altura + 1, decimal_binario << 1 | 1, tabla,binarios);
    }
    if(arbol->L){
        //printf("L >> %d, %c\n", arbol->frec , arbol->dato);
        CrearTabla(arbol->L, altura+1, decimal_binario << 1,tabla,binarios);
    }
    if(!arbol->R && !arbol->L){
        //printf("Pone >> %d, %c\n", arbol->frec , arbol->dato);
        binarios = binario(decimal_binario);
        InsertarTabla(tabla,arbol->dato, altura, decimal_binario,binarios);
    }
}

void obetenerTiraBinaria(NodoBin *listaBin, char *frase,FILE *salidaBin){
    NodoBin *aux, *aux2;
    char *array = "";
    aux = listaBin;
    if(listaBin != NULL){
        for (int i = 0; i < strlen(frase) ; ++i) {
            aux2 = aux;
            while (aux2 != NULL) {
                if(aux2->letra == frase[i]){
                    sprintf(array,"%d",aux2->binary);
                    if (strlen(array) == (aux2->nbits - 1)) {
                        sprintf(array,"0%d",aux2->binary);
                    }
                    fprintf(salidaBin,"%s",array);
                    break;
                }
                aux2 = aux2->sig;
            }
        }
    }
}

void mostrarBinarios(NodoBin *aux){
    while (aux != NULL) {
        printf("Caracter %c >> Bits  %d >> Profundidad %d\n", aux->letra, aux->binary, aux->nbits);
        aux = aux->sig;
    }
}

void *Formatear_texto(char *s){
    int c = 0;
    while(s[c] != '\0'){
        s[c] = tolower(s[c]);
        if (s[c] == '\361' || s[c] == '\321') s[c] = 'n';
        else if (s[c] == '\300' || s[c] == '\301' || s[c] == '\340' || s[c] == '\341') s[c] = 'a';
        else if (s[c] == '\310' || s[c] == '\311' || s[c] == '\350' || s[c] == '\351') s[c] = 'e';
        else if (s[c] == '\314' || s[c] == '\315' || s[c] == '\354' || s[c] == '\355') s[c] = 'i';
        else if (s[c] == '\322' || s[c] == '\323' || s[c] == '\326' || s[c] == '\362' || s[c] == '\363' || s[c] == '\366') s[c] = 'o';
        else if (s[c] == '\331' || s[c] == '\332' || s[c] == '\334' || s[c] == '\371' || s[c] == '\372' || s[c] == '\374') s[c] = 'u';
        else if (s[c] == ' ') s[c] = '#';
        c++;
    }
}

void Contar_Frecuancias(char *s, int *count) {
    int c = 0;
    int rep = 0;
    while (s[c] != '\0') {
        if (s[c] >= 'a' && s[c] <= 'z') {
            count[s[c] - 'a']++;
        }else if(s[c] == '#'){
            count[28]++;
        }else if(s[c] == '.'){
            count[26]++;
        }else if(s[c] == ','){
            count[27]++;
        }
        c++;
    }
}

int Mostrar_Datos(Nodo *lista){
    if(lista != NULL){
        int i = 0;
        while (lista != NULL){
            printf("Letra: %c ; Frec: %d\n", lista -> dato, lista -> frec);
            lista = lista -> sig;
            i++;
        }
        printf("La lista tiene %d datos\n", i);
        return i;
    }else{
        puts("Tu Lista esta vacia\n");
        return 0;
    }
}

void inOrden (Nodo *top){
    if (top != NULL){
        inOrden (top->L);
        printf("Caracter = %c Frecuencia = %d\n",top->dato, top->frec);
        inOrden(top->R);
    }
}

void preOrden (Nodo *top){
    if (top != NULL){
        printf("Caracter = %c Frecuencia = %d\n",top->dato, top->frec);
        preOrden(top->L);
        preOrden(top->R);
    }
}

void preOrden_PIMP (Nodo *top, FILE* fout){
    if (top != NULL){
        fprintf(fout,"%d %c ",top->frec, top->dato);
        preOrden_PIMP (top->L,fout);
        preOrden_PIMP (top->R,fout);
    }
}

Nodo* Alta_Inicial(char dato, int frec, Nodo* cima){
    Nodo *box,*aux;
    box = allocateMem(dato,frec);
    if(cima == NULL){
        return box;
    }else{
        aux = cima;
        while(aux->sig!=NULL){
            aux = aux -> sig;
        }
        aux->sig=box;
    }
    return cima;
}

Nodo *Alta_Dato(Nodo *top, char dato, int frec, int posicion)
{
    Nodo *aux, *nuevo;
    aux = top;
    nuevo = allocateMem(dato, frec);
    if (aux != NULL) {
        while (aux->sig != NULL) {
            if (aux->dato == posicion) {
                nuevo->sig = aux->sig;
                aux->sig = nuevo;
                break;
            } else {
                aux = aux->sig;
            }
        }
    }
    puts("Agregado");
    return top;
}

Nodo *OrdenamientoSeleccion(Nodo *top) {
    Nodo *aux, *aux2;
    aux = top;
    if (top != NULL) {
        while (aux->sig != NULL) {
            aux2 = aux->sig;
            while (aux2 != NULL) {
                if (aux->frec > aux2->frec) {
                    char letra = aux->dato;
                    aux->dato = aux2->dato;
                    aux2->dato = letra;

                    int frec = aux->frec;
                    aux->frec = aux2->frec;
                    aux2->frec = frec;
                }
                aux2 = aux2->sig;
            }
            aux = aux->sig;
        }
    }
    return top;
}

void InsertarOrden(Nodo** Cabeza, Nodo *e){
    Nodo *auxiliar_ref, *auxiliar_asignacion;
    if(!*Cabeza){
        *Cabeza = e;
        (*Cabeza)->sig = NULL;
    }else{
        auxiliar_ref = *Cabeza;
        auxiliar_asignacion = NULL;
        while(auxiliar_ref && auxiliar_ref->frec < e->frec){
            auxiliar_asignacion = auxiliar_ref;
            auxiliar_ref = auxiliar_ref->sig;
        }
        e->sig = auxiliar_ref;
        if(auxiliar_asignacion) auxiliar_asignacion->sig = e;
        else *Cabeza = e;
    }
}

Nodo* constructTreeUtil(char* letra,int pre[], int* preIndex, int low, int high, int size){

    if (*preIndex >= size) {return NULL;}

    Nodo *root = allocateMem(letra[*preIndex],pre[*preIndex]);
    printf("%d %d >> %c %d\n",low,high,letra[*preIndex],pre[*preIndex]);

    *preIndex +=  1;

    if (low == high){
        puts("raiz");
        return root;
    }

    int i;
    for ( i = low; i <= high; ++i ) {
        if (pre[i] < root->frec) {

            break;
        }
    }


    root->L = constructTreeUtil(letra, pre, preIndex, *preIndex, i - 1, size);
    root->R = constructTreeUtil(letra, pre, preIndex, i, high, size);

    return root;
}

Nodo *constructTree(char* letra, int pre[], int size){
    int preIndex = 0;
    return constructTreeUtil(letra ,pre, &preIndex, 0, size - 1, size);
}

int size(Nodo *top){
    if (top==NULL)
        return 0;
    else
        return(size(top->L) + 1 + size(top->R));
}

char* decode_file(Nodo* root, char* s){
    if (root != NULL && root->L != NULL && root->R != NULL){
        char* ans = "";
        Nodo* curr = root;
        for (int i=0;i<strlen(s);i++) {
            if (s[i] == '0') {
                puts("L");
                curr = curr->L;
            } else {
                printf("R : %d >> %c\n", curr->frec, curr->dato);
                curr = curr->R;
            }
            puts("Function dies here");
            if (!curr->R && !curr->L) {
                sprintf(ans, "%c", curr->dato);
                curr = root;
            }
        }
        return ans;
    }else{
        printf("Algo falta\n");
        return NULL;
    }
}



#endif //ALGORITMO_HUFFMAN_FUNCIONES_H