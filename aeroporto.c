#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX 50
#include "fila_solo.h"
#include "pilha_hangar.h"
#include "lista_passageiros.h"
  

int main(){

    Fila_Voo* f = cria_fila();

    Pilha_Hangar* p = cria_pilha();
    
  

    Lista_Passageiros* l = cria_lista();

	

	
	carregaHangar(p);
	carregaSolo(f);
	l = carregaPassageiros(l);

    int opc;
    char nome[TEXT_MAX];
    char sigla[TEXT_MAX];
    char empresa[TEXT_MAX];
	int codigo;   
	int idade;

    do{
        printf ("-------------------------------------------------------\n");
        printf ("Sistema de Controle de Aeroporto do Litoral Norte de RS\n");
        printf ("-------------------------------------------------------\n");
        printf ("[1] Listar todos os avioes em solo\n");
        printf ("[2] Adicionar aviao em solo\n");
        printf ("[3] Remover aviao em solo\n");
        printf ("[4] Listas de todos os avioes no Hangar\n");
        printf ("[5] Adicionar aviao no Hangar\n");
        printf ("[6] Remover aviao no Hangar\n");
        printf ("[7] Listar todos os passageiros\n");
        printf ("[8] Adicionar um Passageiro\n");
        printf ("[9] Remover um passageiro\n");
        printf ("[0] Sair & Salvar Dados\n");
        printf ("-------------------------------------------------------\n");
        scanf ("%d", &opc);
        switch (opc){
        case 1:
            listaAviaoSolo(f);
            system("pause");
			system("cls");
        break;
        case 2:
        	printf ("----------------ADICAO DE AVIAO NO SOLO----------------\n");
        	printf ("Informe o nome do aviao: ");
        	scanf ("%s", nome );
        	printf ("Informe a sigla do aviao: ");
        	scanf ("%s", sigla);
        	printf ("Informe a empresa do aviao: ");
        	scanf ("%s", empresa);
        	printf ("\n");
        	printf("-------------------------------------------------------\n");
        	addAviaoSolo(f, nome, sigla, empresa);
        
            system("pause");
			system("cls");
        break;
        case 3: 
           deleteAviaoSolo(f);
            system("pause");
			system("cls");
        break;
        case 4:
            listaAviaoHangar(p);
            system("pause");
			system("cls");
        break;
        case 5:
        	printf ("---------------ADICAO DE AVIAO NO HANGAR---------------\n");

        	printf ("Informe o nome do aviao: ");
        	scanf ("%s", nome );
        	printf ("Informe a sigla do aviao: ");
        	scanf ("%s", sigla);
        	printf ("Informe a empresa do aviao: ");
        	scanf ("%s", empresa);
        	printf ("\n");
        	printf("-------------------------------------------------------\n");
        	codigo=11;
        	addAviaoHangar(p, codigo, nome, sigla, empresa);
            system("pause");
			system("cls");
        break;
        case 6:
            deleteAviaoHangar(p);
             system("pause");
			system("cls");
        break;
        case 7:
            listaPassageiros(l);
             system("pause");
			system("cls");
        break;
        case 8:
        	printf ("-----------------ADICAO DE PASSAGEIROS-----------------\n");
        	printf ("Informe o codigo do passageiro: ");
        	scanf ("%d", &codigo);
        	printf ("Informe o nome do passageiro: ");
        	scanf ("%s", nome);
        	printf ("Informe a idade do passageiro: ");
        	scanf ("%d" , &idade);
     
        	printf ("\n");
        	printf("-------------------------------------------------------\n");
            l = addPassageiro(l, codigo, nome, idade);
            system("pause");
			system("cls");
        break;
        case 9:
        	printf("-----------------REMOCAO DE PASSAGEIROS-----------------\n");
        	printf("Informe o codigo do passageiro a ser removido: ");
        	scanf ("%d", &codigo);
            l = removePassageiro(l, codigo);
            system("pause");
			system("cls");
        break;
		case 10:
			pilhaInverte(p);
		break;
    	}
    
    	
    } while (opc!= 0);

	salvaHangar(p);
	salvaSolo(f);
	salvaPassageiros(l);
	pilhaLibera(p);
	filaLibera(f);
	listaLibera(l);

    return 0;
}
