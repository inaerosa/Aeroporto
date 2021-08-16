#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX 50

typedef struct pilha Pilha_Hangar;
typedef struct lista_pilha Lista_Hangar;


struct pilha{
    Lista_Hangar * prim;
};

struct lista_pilha{
    int id;
    char nome_aviao[TEXT_MAX];
    char sigla[TEXT_MAX];
    char empresa[TEXT_MAX];
    struct lista_pilha * prox;
};



Pilha_Hangar* cria_pilha(){
    Pilha_Hangar* p = (Pilha_Hangar*) malloc (sizeof(Pilha_Hangar));
    p->prim = NULL;
    return p;
}


void addAviaoHangar(Pilha_Hangar* p, int i, char nome[], char sigla[], char empresa[] ){
    Lista_Hangar *n = (Lista_Hangar *) malloc (sizeof(Lista_Hangar));
    n->id = i;
    strcpy(n->nome_aviao, nome);
    strcpy(n->sigla, sigla);
    strcpy(n->empresa, empresa);
    n->prox = p->prim;
    p->prim = n;
    printf ("Aviao adicionado ao Hangar\n");
}

void deleteAviaoHangar(Pilha_Hangar* p){

    Lista_Hangar * aux;

    if (p->prim != NULL){
        aux = p->prim;
        p->prim = aux ->prox;
        free (aux);
    } else {
        printf ("Atencao! Hangar vazio\n");
    }
}

void listaAviaoHangar(Pilha_Hangar * p){
    Lista_Hangar * aux;
    aux = p->prim;
    printf ("--------------AVIOES NO HANGAR-----------------\n");
    while (aux != NULL){
        printf ("Indice:  %d |\t", aux->id);
        printf ("Nome do aviao: %s |\t ", aux->nome_aviao);
        printf ("Sigla: %s |\t", aux->sigla);
        printf ("Empresa: %s |\n", aux->empresa);
		aux = aux ->prox;
    }
}

void pilhaLibera (Pilha_Hangar* p){
    Lista_Hangar * aux = p->prim;
    while (aux!= NULL){
        Lista_Hangar * t = aux->prox;
        free(aux); 
        aux=t;
    }
    free(p);
}

Pilha_Hangar *pilhaInverte(Pilha_Hangar *p){
	Pilha_Hangar *auxP = cria_pilha();
	Lista_Hangar *aux;
	aux = p->prim;
	while (aux != NULL){
		addAviaoHangar(auxP, aux->id, aux->nome_aviao, aux->sigla, aux->sigla);
		aux = aux -> prox;
	}
	return auxP;
}


void salvaHangar(Pilha_Hangar* p){
	FILE *txt_hangar;
	
	if ((txt_hangar = fopen ("Avioes-Hangar.txt", "w+"))== NULL){
		printf ("Erro ao abrir o arquivo\n");
	} else {
		p = pilhaInverte(p);
		Lista_Hangar* aux;
		aux = p->prim;
		while (aux !=NULL){
			fprintf (txt_hangar, "%d| %s | %s | %s | \n", aux->id, aux->nome_aviao, aux->sigla, aux->empresa);
			aux = aux->prox;	
		}
	}
	fclose(txt_hangar);
}



void carregaHangar(Pilha_Hangar * p){
	FILE *txt_hangar;
    int id;
	char nome_aviao[TEXT_MAX];
	char sigla[TEXT_MAX];
	char empresa[TEXT_MAX];
	char * ultima;
	char linha[1024];
	int indice = 0;
	if ((txt_hangar = fopen("Avioes-Hangar.txt", "r"))== NULL){
		printf ("Erro ao abrir o arquivo\n");
	} else{
		while (!feof(txt_hangar)){
		fgets(linha, 1024, txt_hangar);
		ultima = strtok (linha, "|");
			for (indice = 0; ultima != NULL; indice++){
			
				if (indice == 0){
					id = atof(ultima);
				} else if (indice == 1){
					strcpy(nome_aviao,ultima);
				} else if(indice == 2) {
					strcpy(sigla, ultima);
				} else if (indice == 3) {
					strcpy(empresa, ultima);
				}
				
				ultima = strtok(NULL,  "|");
			}
			addAviaoHangar(p, id, nome_aviao, sigla, empresa);
		}
	}
	fclose(txt_hangar);
}


