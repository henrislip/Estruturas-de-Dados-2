#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} Arvore;

Arvore* cria_vazia (void)
{
   return NULL;
}

void imprime_abb_in_ordem (Arvore* a)
{
   if (a != NULL)
   {
      imprime_abb_in_ordem(a->esq);
      printf("%d\n",a->info);
      imprime_abb_in_ordem(a->dir);
   }
}

Arvore* cria(int info){
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    a->info = info;
    a->esq = a->dir = NULL;
    return a;
}

Arvore* insere(Arvore* a, int info){
    if (a==NULL) {
        a = cria(info);
    }
    else
        if (info < a->info){
            a->esq = insere(a->esq,info);
        }
        else {
            a->dir = insere(a->dir,info);
        }

    return a;
}

Arvore* remover (Arvore* a, int v){
  Arvore* aux;
  int salva = 1;
  if(a == NULL) return NULL;           
      
      if(a->info == v){ 
            //folha
             if(a->dir == NULL && a->esq == NULL){
                a->esq = NULL;
                a->dir = NULL;
                a = NULL;
                free(a);
                return NULL;
              }
            //com 1 filho na esquerda
              else if(a->esq != NULL && a->dir == NULL){ 
              a = a->esq; 
              return a;
              } 
            //com 1 filho na direita
                else if(a->dir != NULL && a->esq == NULL){ 
                a = a-> dir;
                return a;
                }
            //com 2 filhos
                  else if(a->dir != NULL && a->esq != NULL){
                    aux=a->esq;
                      while(aux->dir != NULL)
                      {
                       aux=aux->dir;
                      }
                    a = remover(a,aux->info);
                    a->info = aux->info;
                    return a;
                  }
      }
      else if(v < a->info) a->esq = remover(a->esq,v);
      else if(v > a->info) a->dir = remover(a->dir,v);      
}


Arvore* busca (Arvore* a, int v){
  if (a == NULL) return NULL;
    if(a->info == v) return a;
    else if(v < a->info){
          busca(a->esq,v);
    }
    else if (v > a->info){
          busca(a->dir,v);
    }
}


int contaNo(Arvore *a){
   if(a == NULL)
        return 0;
   else
        return 1 + contaNo(a->esq) + contaNo(a->dir);
}

int somaNo(Arvore *a){
   if(a == NULL)
        return 0;
   else
        return a->info + somaNo(a->esq) + somaNo(a->dir);
}

int profundidade(Arvore* a, int v,int cont){
  ++cont;
  if (a == NULL) return 0;
    if(a->info == v) return cont;
    else if(v < a->info){
          profundidade(a->esq,v,cont);
    }
    else if (v > a->info){
          profundidade(a->dir,v,cont);
    }
}

int iguais(Arvore* a,Arvore* b){
  if(a==NULL && b==NULL)
    return 1;
  if(a==NULL || b==NULL)
    return 0;
  return ((a->info==b->info) && iguais(a->esq,b->esq) && iguais(a->dir,b->dir));
}

Arvore* min(Arvore* a){
  if (a->esq == NULL) return a;
  else if(a != NULL){
    min(a->esq);
  }
}

void inOrder(Arvore *a){
    if (a != NULL){
        inOrder(a->esq);
        printf("%d ", a->info);
        inOrder(a->dir);
    }
}

void preOrder(Arvore *a){
    if (a != NULL){
        printf("%d ", a->info);
        preOrder(a->esq);
        preOrder(a->dir);
    }
}

void posOrder(Arvore *a){
    if (a != NULL){
        posOrder(a->esq);
        posOrder(a->dir);
        printf("%d ", a->info);
    }
}

Arvore* max(Arvore* a){
  if (a->dir == NULL) return a;
  else if(a != NULL){
    max(a->dir);
  }
}

int main()
{
    Arvore* b,*c;
    Arvore* arvore, *nova;
    int result = 0, result2 = 0,result3 = 0;


    arvore = cria_vazia();
    arvore = insere(arvore,10);
    arvore = insere(arvore,6);
    arvore = insere(arvore,15);
    arvore = insere(arvore,5);
    arvore = insere(arvore,7);
    arvore = insere(arvore,13);
    arvore = insere(arvore,19);
    arvore = insere(arvore,20);
    arvore = insere(arvore,1);
    printf("\n");

    //imprime_abb_in_ordem(arvore);
    //printf("\n");
   // b = busca(arvore,1);
  // printf("%d\n",b!=NULL);
  // printf("\n");
   //arvore = remover(arvore,10);
   //printf("\n");
   //imprime_abb_in_ordem(arvore);
   //printf("\n\n\n");
   //arvore = remover(arvore,1);
   //imprime_abb_in_ordem(arvore);
   result = contaNo(arvore);
   printf("%d\n",result);
   //result2 = somaNo(arvore);
   //printf("%d\n",result2);
   //result3 = profundidade(arvore,20,0);
   //printf("%d\n",result3);

   //printf("se sao iguais 1 senao 0 se falsas %d\n",iguais(arvore,arvore));

   //b = min(arvore);
   //printf("o minimo encontrado %d\n",b->info);

   //c = max(arvore);
   //printf("o maximo encontrado %d\n",c->info);
   printf("preOrder\n"); 
   preOrder(arvore);
   printf("\n");
   printf("inOrder\n");
   inOrder(arvore);
   printf("\n");
   printf("posOrder\n");
   posOrder(arvore);
   printf("\n");
   return 0;
}


