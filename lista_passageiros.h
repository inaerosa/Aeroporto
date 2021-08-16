#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX 50

typedef struct lista Lista_Passageiros;

struct lista{
    int id;
    char nome_passageiro[TEXT_MAX];
    int idade;
    struct lista*proximo;
};

Lista_Passageiros * cria_lista(){
    return (NULL);
}

Lista_Passageiros * addPassageiro(Lista_Passageiros * l, int id, char nome[], int idade){
	
    Lista_Passageiros * no = (Lista_Passageiros *) malloc (sizeof(Lista_Passageiros));
    
    if (l != NULL){
        Lista_Passageiros *anterior = l;
        Lista_Passageiros *prox = l;
        Lista_Passageiros *atual = l;

        while (idade < prox->idade && prox->proximo != NULL){
            anterior = atual;
            atual = prox;
            prox = prox->proximo;
        }

        if (idade < prox->idade && prox->proximo == NULL){
            no->idade = idade;
            no->id = id;
            strcpy(no->nome_passageiro, nome);
            prox->proximo = no;
            no->proximo = NULL;
            return (l);
        } 

        if (idade < atual->idade){
            no->idade = idade;
            no->id = id;
            strcpy(no->nome_passageiro, nome);
            atual->proximo = no;
            no->proximo = prox;
            return (l);
        }
    }
    no->id = id;
    no->idade = idade;
    strcpy(no->nome_passageiro, nome);
    no->proximo = l;
    return (no);
    
}

int verificaPassageiro(Lista_Passageiros *l, int codigo){
	
	Lista_Passageiros * aux;
	
	for (aux = l; aux != NULL; aux = aux->proximo){
		if (codigo == aux->id){
			printf ("Atencao, codigo já está em uso!\n ");
			printf ("Informe outro codigo: ");
			scanf ("%d", &codigo);
		}
	}
	return codigo;
}

void listaPassageiros(Lista_Passageiros *l){
    Lista_Passageiros * aux;
 printf ("--------------LISTA DE PASSAGEIROS-----------------\n");
    for (aux = l; aux!=NULL; aux = aux->proximo){
        printf ("Codigo: %d | \t", aux->id);
        printf("Idade: %d | \t", aux->idade);
        printf ("Nome do passageiro: %s | \t\n", aux->nome_passageiro);
    }

}

Lista_Passageiros * removePassageiro(Lista_Passageiros * l, int id){
	
    Lista_Passageiros * anterior = NULL;
    Lista_Passageiros * atual = l;

    while (atual != NULL && atual->id != id){
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL){
        printf ("Passageiro nao encontrado!\n");
        return (l);
    }
    if (anterior == NULL){
        l = l->proximo;
    } else {
        anterior->proximo = atual->proximo;
        
    	printf("Passageiro removido!\n")    ;
    }
	
    free(atual);
    return (l);
}

void listaLibera(Lista_Passageiros ** l){
      while (*l != NULL) {
           Lista_Passageiros * aux = (*l)->proximo; 
           *l = NULL; 
           free(*l); 
           *l = aux; 
      }
 }
 

Lista_Passageiros *carregaPassageiros(Lista_Passageiros * l){

    FILE *txt_passageiros;

    char nome[TEXT_MAX];
    int id;
    int idade;
    char * ultima;
   	char linha[1024];
   	
    int index;
    if ((txt_passageiros = fopen("Lista-Passageiros.txt", "r"))== NULL){
        printf ("Erro ao abrir o arquivo!\n");
    } else {
        while (!feof(txt_passageiros)){ 
   		fgets(linha, 1024, txt_passageiros); 
   		ultima = strtok (linha, "	|	"); 
			for(index = 0; ultima != NULL; index++){
				if(index==0){ 
					id = atof(ultima);
				} else if (index==1){ 
					strcpy(nome, ultima); 
				} else {
					idade = atof(ultima); 
				}
				ultima = strtok (NULL, "|"); 
			}
			l = addPassageiro(l, id, nome, idade);
		}
       
    }
     fclose(txt_passageiros);
	return l;
}

void salvaPassageiros(Lista_Passageiros *l){
	FILE *txt_passageiros;
	Lista_Passageiros * aux;
	
	if ((txt_passageiros = fopen ("Lista-Passageiros.txt", "w+"))== NULL){
		printf ("Erro ao abrir o arquivo\n");
	} else {
		for (aux = l; aux!=NULL; aux = aux->proximo){
			fprintf (txt_passageiros,"%d	|	%s	|	%d\n",  aux->id, aux->nome_passageiro, aux->idade);
    	}	
	}
	fclose(txt_passageiros);
}
