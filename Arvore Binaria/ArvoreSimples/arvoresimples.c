#include <stdio.h>
#include <stdlib.h>

struct arvore {
    char info;
    struct arvore *esq;
    struct arvore *dir;
};

typedef struct arvore Arvore;

Arvore *cria_vazia() {
    return NULL;
}

Arvore *cria (char c, Arvore *sae, Arvore *sad) {
    Arvore *p = (Arvore*) malloc(sizeof(Arvore));
    p->info = c;
    p->esq = sae;
    p->dir = sad;
    return p;
}

int eh_vazia (Arvore *a) {
    return a == NULL;
}

Arvore *libera (Arvore *a){
    if (!eh_vazia(a)){
        libera(a->esq); /* libera sae */
        libera(a->dir); /* libera sad */
        	free(a); /* libera raiz */
    }
    return NULL;
}

int pertence (Arvore *a, char c){
    if (eh_vazia(a))
        return 0; /* arvore vazia: nao encontrou */
    else
        return a->info==c ||
        pertence(a->esq,c) ||
        pertence(a->dir,c);
}

void imprime (Arvore *a) {
    if (!eh_vazia(a)) {
        printf("%c ", a->info); /* mostra raiz */
        imprime(a->esq); /* mostra sae */
        imprime(a->dir); /* mostra sad */
    }
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

/*char searchIterativo(Arvore* h, char v) {
    Arvore* aux = h;
   while(h != NULL || h->info != v){
         if(h == NULL||h->info == v)
            return aux->info; 
        if(h->info > v){
             aux = h;
             h = h->esq;
        }     
        else{
             aux = h;
             h = h->dir;
        }     
   }
   return NULL;
}*/

int contano(Arvore *a,int cont) {
    if (!eh_vazia(a)) {
        printf("%d \n",cont); /* mostra raiz */
        contano(a->esq,++cont); /* mostra sae */
        contano(a->dir,++cont); /* mostra sad */
    }
  return cont;  
}  

void main() {
    int result;
    char letr = 'b';
    Arvore *a0 = cria('k', cria_vazia(),cria_vazia());

    Arvore *a1 = cria('j', a0,cria_vazia());
    Arvore *a2 = cria('i', cria_vazia(),a1);
    Arvore *a3 = cria('h',a2,cria_vazia());
   	Arvore *a4 = cria('g',cria_vazia(),cria_vazia());
   	Arvore *a5 = cria('f',cria_vazia(),cria_vazia());
   	Arvore *a6 = cria('e',a5,a4);
   	Arvore *a7 = cria('c',cria_vazia(),cria_vazia());
   	Arvore *a8 = cria('d',a6,a3);
   	Arvore *a9 = cria('b',a7,cria_vazia());
   	Arvore *a10 = cria('a',a9,a8);

    imprime(a10); printf("\n");
     printf("Altura da arvore: %d\n", alturaArvore(a10,-1));
     printf("O grau da arvore: %d\n", grauArvore(a10));

    result = contano(a10,0);
    printf("%d\n",result);

}