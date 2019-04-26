//
// Created by MrJuancho on 11/04/2019.
//

#ifndef ALGORITMO_HUFFMAN_FUNCIONES_H
#define ALGORITMO_HUFFMAN_FUNCIONES_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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
    char *binary;

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

NodoBin* allocateMemBin(char letra, long int bits, char nbits,char* binary){
    NodoBin* dummy;
    dummy = (NodoBin*)malloc(sizeof(NodoBin));
    dummy -> letra = letra;
    dummy -> bits = bits;
    dummy -> nbits = nbits;
    dummy ->binary = binary;
    dummy -> sig = NULL;
    return dummy;
}

void InsertarTabla(NodoBin** Tabla,char caracter,long int altura, int valor,char *referencias){
    NodoBin *auxiliar, *auxiliar_ref, *auxiliar_asignacion;
    auxiliar = allocateMemBin(caracter,valor,altura,referencias);
    if(!*Tabla){
        *Tabla = auxiliar;
        (*Tabla)->sig = NULL;
    }else{
        auxiliar_ref = *Tabla;
        auxiliar_asignacion = NULL;
        while(auxiliar_ref && auxiliar_ref->letra < auxiliar->letra){
            auxiliar_asignacion = auxiliar_ref;
            auxiliar_ref = auxiliar_ref->sig;
        }
        auxiliar->sig = auxiliar_ref;
        if(auxiliar_asignacion) auxiliar_asignacion->sig = auxiliar;
        else *Tabla = auxiliar;
    }
}

void CrearTabla(Nodo *arbol, int altura, int rec_binario, NodoBin **tabla)
{
    if(arbol->R)  CrearTabla(arbol->R, altura+1, rec_binario << 1|1,tabla);
    if(arbol->L) CrearTabla(arbol->L, altura+1, rec_binario << 1,tabla);
    if(!arbol->R && !arbol->L){
        InsertarTabla(tabla,arbol->dato, altura, rec_binario,"");
    }
}

int binario (int n) {
    if(n==0) {
        return n;
    }else {
        return binario(n / 2) * 10 + n % 2;
    }
}

void implementarbin(NodoBin *Arbol) {
    if (Arbol != NULL) {
        int t = strlen(Arbol->binary);
        if (t == (Arbol->nbits - 1)) {
            char *array = "";
            sprintf(array,"0%s",Arbol->binary);
            Arbol->binary = array;
        }
    }
}

void mostrarBinarios(NodoBin *top){
    if(top != NULL){
        while(top != NULL){
            printf("Caracter %c >> Bits  %s >> Profundidad %d\n", top->letra, top->binary, top->nbits);
            top = top->sig;
        }
    }
}

NodoBin *ordenarApariciones(NodoBin *Binarios, char *string){
    NodoBin *aux = Binarios;
    for (int i = 0; i < strlen(string) ; ++i) {
        if (aux->letra == string[i]){
            aux = aux->sig;
        }else{
            char letra = aux->letra;
            aux->letra = string[i];
            string[i] = letra;
        }
    }
    return Binarios;
}

char* guardarBinarios(NodoBin* top,FILE *fout) {
    NodoBin *aux = top;
    char* binarios = "";
    if (aux != NULL) {
        char *array = "";
        while (aux->sig != NULL) {
            int codigo = binario(aux->bits);
            sprintf(array, "%d", codigo);
            aux->binary = array;
            implementarbin(aux);
            fprintf(fout,"%s",aux->binary);
            aux = aux->sig;
        }
    }
    return binarios;
}

NodoBin *BuscaCaracter(NodoBin *Tabla, unsigned char c)
{
    NodoBin *t;
    t = Tabla;
    while(t && t->letra != c) t = t->sig;
    return t;
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
        c++;
    }
}

void Contar_Frecuancias(char *s, int *count,char* acomodados) {
    int c = 0;
    int rep = 0;
    while (s[c] != '\0') {
        if (s[c] >= 'a' && s[c] <= 'z') {
            acomodados[c] = s[c];
            count[s[c] - 'a']++;
        }else if(s[c] == ' '){
            acomodados[c] = '#';
            count[28]++;
        }else if(s[c] == '.'){
            acomodados[c] = s[c];
            count[26]++;
        }else if(s[c] == ','){
            acomodados[c] = s[c];
            count[27]++;
        }
        c++;
    }
}

void Mostrar_Datos(Nodo *lista){
    if(lista != NULL){
        int i = 0;
        while (lista != NULL){
            printf("Letra: %c ; Frec: %d\n", lista -> dato, lista -> frec);
            lista = lista -> sig;
            i++;
        }
        printf("La lista tiene %d datos\n", i);
    }else{
        puts("Tu Lista esta vacia\n");
    }
}

void inOrden (Nodo *top){
    if (top != NULL){
        inOrden (top->L);
        printf("Elemento = %d\n",top->dato);
        inOrden(top->R);
    }
}

void preOrden (Nodo *top){
    if (top != NULL){
        printf("Caracter = %c Frecuencia = %d\n",top->dato, top->frec);
        preOrden (top->L);
        preOrden(top->R);
    }
}

void preOrden_PIMP (Nodo *top, FILE* fout){
    if (top != NULL){
        fprintf(fout,"\r%c %d ",top->dato, top->frec);
        preOrden_PIMP (top->L,fout);
        preOrden_PIMP (top->R,fout);
    }
}

void postOrden (Nodo *top){
    if (top != NULL){
        preOrden (top->L);
        preOrden(top->R);
        printf("Elemento = %d\n",top->dato);
    }
}

void alta(Nodo ** top, char dato, int frec)
{
    if(*top == NULL){
        *top = allocateMem(dato, frec);
    }
    else if(dato < (*top)->dato){
        alta(&(*top)->L,dato,frec);
    }
    else{
        alta(&(*top)->R,dato,frec);
    }
}

void moveleft(Nodo **top)
{
    Nodo *auxiliar_asignacion,*auxiliar_ref;
    auxiliar_ref=(*top);
    auxiliar_asignacion=(*top)->L;
    while(auxiliar_asignacion->R!=NULL)
    {
        auxiliar_ref=auxiliar_asignacion;
        auxiliar_asignacion=auxiliar_asignacion->R;
    }
    (*top)->dato=auxiliar_asignacion->dato;
    if(auxiliar_ref==(*top))
    {
        auxiliar_ref->L=auxiliar_asignacion->L;
    }
    else
    {
        auxiliar_ref->R=auxiliar_asignacion->L;
    }
    (*top)=auxiliar_asignacion;
}

void baja(Nodo **top,int dato)
{
    Nodo *aux;
    if(*(top)==NULL)
    {
        puts("El arbol esta vacio");
    }
    else
    {
        if(dato<(*top)->dato)
        {
            baja(&(*top)->L,dato);
        }
        else if(dato>(*top)->dato)
        {
            baja(&(*top)->R,dato);
        }
        if(dato==(*top)->dato)
        {
            aux = (*top);
            if (aux->L==NULL)
            {
                (*top)=aux->dato;
            }
            else if(aux->R==NULL)
            {
                (*top)=aux->L;
            }
            else
            {
                moveleft(&aux);
            }
            free(aux);
        }
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

int size(Nodo *top)
{
    if (top==NULL)
        return 0;
    else
        return(size(top->L) + 1 + size(top->R));
}

#endif //ALGORITMO_HUFFMAN_FUNCIONES_H
