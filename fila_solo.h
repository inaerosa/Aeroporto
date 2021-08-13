#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX 50

typedef struct fila Fila_Voo;
typedef struct lista_fila Lista_Voo;

struct fila {
    Fila_Voo* ini;
    Fila_Voo* fim;
};


Fila_Voo* cria_fila(){
    Fila_Voo* f = (Fila_Voo*) malloc (sizeof(Fila_Voo));
    f->ini = f->fim = NULL;
    return f;
}



struct lista_fila{
    char nome_aviao[TEXT_MAX];
    char sigla[TEXT_MAX];
    char empresa[TEXT_MAX];
    Lista_Voo* prox;
};

void addAviaoSolo(Fila_Voo *f, char nome_aviao[], char sigla[], char empresa[] ){
    Lista_Voo * l = (Lista_Voo*) malloc (sizeof(Lista_Voo));
    Lista_Voo* prox;

    strcpy(l->nome_aviao, nome_aviao );
    strcpy(l->sigla, sigla);
    strcpy(l->empresa, empresa);
    l->prox = NULL;
    prox = f->fim;
    if (f->ini == NULL){
        f->ini = l;
        f->fim = l;
        printf ("Aviao adicionado no solo!\n");
    } else {
        prox->prox = l;
        f->fim = l;
        printf ("Aviao adicionado no solo!\n");
    } 
}

void listaAviaoSolo(Fila_Voo *f){
    Lista_Voo * aux;
    aux = f->ini;
    printf ("---------------AVIOES NO SOLO-----------------\n");

    while (aux != NULL){
        printf ("Nome do aviao: %s\n", aux->nome_aviao);
        printf ("Sigla: %s\n", aux->sigla);
        printf ("Empresa: %s\n\n", aux->empresa);
        aux = aux->prox;
    }
  
}

void deleteAviaoSolo(Fila_Voo *f){
    Lista_Voo * aux;
    if (f->fim == NULL){
        printf ("Pista Vazia!");
    } else {
        aux = f->ini;
        f->ini = aux -> prox;
        free(aux);
        printf ("Aviao removido!\n");
    } 
    
}

void filaLibera(Fila_Voo *f){
    free(f);
}

void salvaSolo(Fila_Voo* f){
	FILE *txt_solo;
	
	if ((txt_solo = fopen ("Avioes-Solo.txt", "w+"))==NULL){
		printf ("Erro ao abrir o arquivo solo\n");
	} else {
		Lista_Voo* aux;
		aux = f->ini;
		while (aux != NULL){
			fprintf (txt_solo, "%s | %s | %s | \n", aux->nome_aviao, aux->sigla, aux->empresa);
			aux = aux->prox;
		}
	}
}



void carregaSolo(Fila_Voo * f){
    
    FILE *txt_solo;

   	char nome_aviao[TEXT_MAX];
   	char sigla[TEXT_MAX];
   	char empresa[TEXT_MAX];
   	char * ultima;
   	char linha[1024];
	int indice;
		char caractere;
   	if ((txt_solo = fopen("Avioes-Solo.txt", "r"))== NULL){
   		printf ("Erro ao abrir o arquivo\n");
	} else{
	while (!feof(txt_solo)){
		fgets(linha, 1024, txt_solo);
		ultima = strtok (linha, "|");
			for (indice = 0; ultima != NULL; indice++){
				if (indice == 0){
					strcpy(nome_aviao,ultima);
				} else if (indice == 1){
					strcpy(sigla, ultima);
				} else if (indice == 2){
					strcpy(empresa, ultima);
				}
				
				ultima = strtok(NULL,  "|");
			}
			addAviaoSolo(f, nome_aviao, sigla, empresa);
		}
	}
	
	fclose(txt_solo);
}


