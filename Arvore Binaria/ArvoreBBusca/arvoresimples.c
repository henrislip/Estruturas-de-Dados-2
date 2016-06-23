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


void main() {
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
    


}