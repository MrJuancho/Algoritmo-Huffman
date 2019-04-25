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

void Contar_Frecuancias(char *s, int *count) {
    int c = 0;
    while (s[c] != '\0') {
        if (s[c] >= 'a' && s[c] <= 'z')
            count[s[c]-'a']++;
        else if(s[c] == ' ') count[26]++;
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
    Nodo *a,*p;
    p=(*top);
    a=(*top)->L;
    while(a->R!=NULL)
    {
        p=a;
        a=a->R;
    }
    (*top)->dato=a->dato;
    if(p==(*top))
    {
        p->L=a->L;
    }
    else
    {
        p->R=a->L;
    }
    (*top)=a;
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
    Nodo *p, *a;
    if(!*Cabeza){
        *Cabeza = e;
        (*Cabeza)->sig = NULL;
    }else{
        p = *Cabeza;
        a = NULL;
        while(p && p->frec < e->frec){
            a = p;
            p = p->sig;
        }
        e->sig = p;
        if(a) a->sig = e;
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
