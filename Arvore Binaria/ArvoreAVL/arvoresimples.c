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

int eh_vazia (Arvore *a) {
    return a == NULL;
}

int pertence (Arvore *a, char c){
    if (eh_vazia(a))
        return 0; /* arvore vazia: nao encontrou */
    else
        return a->info==c ||
        pertence(a->esq,c) ||
        pertence(a->dir,c);
}

int alturaArvore(Arvore *a, int cont){
    int aux = cont;
    if (!eh_vazia(a)){
        int asum = alturaArvore(a->esq, aux + 1);
        int bsum = alturaArvore(a->dir, aux + 1);
        if(asum >= bsum){
        aux = asum;
        }else{
            aux = bsum;
        }
    }
return aux;

}    

int grauArvore(Arvore *a) {
int n_esq,n_dir;    
    if (!eh_vazia(a)) {
      if(a->esq != NULL && a->dir != NULL) return 2;
            else if(a->esq != NULL){
                n_esq = grauArvore(a->esq)==2? 2: 1;
            }
            else if(a->dir != NULL){
                n_dir = grauArvore(a->dir)==2? 2: 1;
            }
        return n_esq > n_dir? n_esq:n_dir;  
    }
}   

int quantidadeNos(Arvore *a){
    if(a->esq != NULL && a->dir == NULL) return 1;
    if(a->esq != NULL && a->dir != NULL) return 2;
    if(a->esq == NULL && a->dir != NULL) return 1;
    else return 0;
}

int isCheia(Arvore *a){ // 0 = cheia 1 = não-cheia
    if(a == NULL){
        return 0;
    }
    if(alturaArvore(a->esq,-1) != alturaArvore(a->dir,-1)){
        return 1;
    }
    if(quantidadeNos(a->esq) != 2 && quantidadeNos(a->esq) != 0) {
        return 1;
    }
    if(quantidadeNos(a->dir) != 2 && quantidadeNos(a->dir) != 0) {
        return 1;
    }
    if(quantidadeNos(a->dir) != quantidadeNos(a->esq)){
        return 1;
    }

     return 0;
}

Arvore *retornaPai(Arvore *a, char elemento){
        printf("BLA");
        if(a == NULL) return NULL;
        if(a->esq == NULL || a->dir == NULL) return NULL;
        if(a->esq->info == elemento || a->dir->info == elemento) return a;

        Arvore *retorno = retornaPai(a->esq, elemento);
        if(retorno == NULL){
            retorno = retornaPai(a->dir, elemento);
        }

        return retorno;
}



void imprime_abb_in_ordem (Arvore* a){
   if (a != NULL){
      imprime_abb_in_ordem(a->esq);
      printf("%d\n",a->info);
      imprime_abb_in_ordem(a->dir);
   }
}

void imprime_abb_in_ordem_fat(Arvore* a){
   if (a != NULL){
      imprime_abb_in_ordem(a->esq);
      printf("%d ALT -> %d\n",a->info,a->fat);
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


