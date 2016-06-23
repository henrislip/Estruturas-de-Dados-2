#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} Arvore;

Arvore* cria_vazia (void){
   return NULL;
}

void imprime_abb_in_ordem (Arvore* a){
   if (a != NULL){
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
                      while(aux->dir != NULL){
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

int main(){
    Arvore* b;
    Arvore* arvore, *nova;

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

    imprime_abb_in_ordem(arvore);
    printf("\n");
   // b = busca(arvore,1);
  // printf("%d\n",b!=NULL);
  // printf("\n");
   arvore = remover(arvore,10);
   printf("\n");
   imprime_abb_in_ordem(arvore);
   printf("\n\n\n");
   arvore = remover(arvore,1);
   imprime_abb_in_ordem(arvore);

   return 0;
}


