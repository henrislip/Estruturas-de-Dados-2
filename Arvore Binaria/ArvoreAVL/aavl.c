#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arvore {
  int info;
  int altnegra;
  struct arvore *esq;
  struct arvore *dir;
}Arvore;

Arvore* cria_vazia (void){
   return NULL;
}

int eh_vazia (Arvore *a){
    return a == NULL;
}

/*void imprime_abb_in_ordem (Arvore* a){
   if (a != NULL)
   {
      imprime_abb_in_ordem(a->esq);
      printf("%d\n",a->info);
      imprime_abb_in_ordem(a->dir);
   }
}*/

void imprime_abb_in_ordem(Arvore* a){
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
    a->fat = 0;
    return a;
}
int pertence (Arvore *a, char c){
    if (eh_vazia(a))
        return 0; /* arvore vazia: nao encontrou */
    else
        return a->info==c ||
        pertence(a->esq,c) ||
        pertence(a->dir,c);
}

int altura(Arvore *a){
    int esq, dir;
    if (a == NULL) return -1;

    esq = altura(a->esq);
    dir = altura(a->dir);

    if (esq > dir)
        return esq + 1;
    else
        return dir + 1;
}

int alturaNegra(Arvore *a, int cont){
    int aux = cont;
    int asum,bsum;
    if (!eh_vazia(a)){
        
        if(a->cor == 'v') asum = alturaNegra(a->esq, aux);
        else if(a-> == 'p'){
         asum = alturaNegra(a->esq, aux + 1);
         bsum = alturaNegra(a->dir, aux + 1);
        }
        

        if(asum > bsum) a->altnegra = asum;
        else a->altnegra = bsum;
        
        if(asum >= bsum)
          aux = asum;
        }
        else{
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
        if(a == NULL) return NULL;
        if(a->esq == NULL || a->dir == NULL) return NULL;
        if(a->esq->info == elemento || a->dir->info == elemento) return a;

        Arvore *retorno = retornaPai(a->esq, elemento);
        if(retorno == NULL){
            retorno = retornaPai(a->dir, elemento);
        }

        return retorno;
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


int isAvl(Arvore* a){
	if(a != NULL){
		isAvl(a->esq);
		isAvl(a->dir);
		if((a->fat < -1) || (a->fat > 1)){
			if(a->fat < 0){
				printf("esquerda\n");
				if((a->esq != NULL)&&(a->esq->fat < 0)){
					printf("esquerda\n");
				}
				else if((a->dir != NULL)&&(a->dir->fat > 0)){
					printf("direita\n");
				}
			}

			if(a->fat > 0){
				printf("direita\n");
				if((a->dir != NULL)&&(a->dir->fat > 0)){
					printf("direita\n\n");
				}
				else if((a->esq != NULL)&&(a->esq->fat < 0)){
					printf("esquerda\n\n");
				}
			}	
		
		}
	}
}

int main(){
    Arvore* b;
    Arvore* arvore, *nova;
    int aux;
    aux = 2;

    arvore = cria_vazia();
    arvore = insere(arvore,10);
    arvore = insere(arvore,6);
    arvore = insere(arvore,15);
    arvore = insere(arvore,5);
    arvore = insere(arvore,7);
 	arvore = insere(arvore,13);
    arvore = insere(arvore,19);
    arvore = insere(arvore,20);

    arvore = insere(arvore,22);

    

    arvore = insere(arvore,1);
    arvore = insere(arvore,2);
    printf("\n");

   // b = busca(arvore,1);
  // printf("%d\n",b!=NULL);
  // printf("\n");

   printf("\n\n\n");
   alturaArvore(arvore,-1);
   imprime_abb_in_ordem(arvore);
   printf("\n\n\n");

   isAvl(arvore);




   return 0;
}


