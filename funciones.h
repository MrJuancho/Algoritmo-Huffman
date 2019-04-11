//
// Created by MrJuancho on 11/04/2019.
//

#ifndef ALGORITMO_HUFFMAN_FUNCIONES_H
#define ALGORITMO_HUFFMAN_FUNCIONES_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct _Nodo{
    int dato;
    struct _Nodo *L;
    struct _Nodo *R;
}Nodo;

Nodo* allocateMem(int dato)
{
    Nodo* dummy;
    dummy = (Nodo*)malloc(sizeof(Nodo));
    dummy -> dato = dato;
    dummy -> R = NULL;
    dummy -> L = NULL;
    return dummy;
}

char *Formatear_texto(char *s){
    int c = 0;
    while(s[c] != '\0'){
        s[c] = tolower(s[c]);
        if(s[c] == 'á' || s[c] == 'à'){

        }else if(){

        }
        c++;
    }
    return
}

void Contar_Frecuancias(char *s, int *count) {
    int c = 0;
    while (s[c] != '\0') {
        if (s[c] >= ' ' && s[c] <= '~' )
            count[s[c]-'a']++;
        c++;
    }
}

Nodo *Obtener_Frase(FILE *file,char *filename){
    int q,
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
        printf("Elemento = %d\n",top->dato);
        preOrden (top->L);
        preOrden(top->R);
    }
}

void postOrden (Nodo *top){
    if (top != NULL){
        preOrden (top->L);
        preOrden(top->R);
        printf("Elemento = %d\n",top->dato);
    }
}

void alta(Nodo ** top, int dato)
{
    if(*top == NULL){
        *top = allocateMem(dato);
    }
    else if(dato < (*top)->dato){
        alta(&(*top)->L,dato);
    }
    else{
        alta(&(*top)->R,dato);
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

int size(Nodo *top)
{
    if (top==NULL)
        return 0; //if the current top is null return a 0 so no add 1 is done
    else
        return(size(top->L) + 1 + size(top->R));
}

#endif //ALGORITMO_HUFFMAN_FUNCIONES_H
