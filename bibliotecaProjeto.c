#include "bibliotecaProjeto.h"
#include "bibliotecaAuxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

Familia *insere_familia(Familia **prim, char *nome, int qtdP){
    
	Familia *familiaB = buscaFamilia(*prim, nome);
	if(familiaB != NULL){
		printf("Erro em: insere_familia.\nNome igual de familias (%s).\n", nome);
        exit(1);
	}
	Familia *novo = alocaFamilia(nome,qtdP);
    Familia *cont = *prim;
    
    if((*prim)==NULL){
        if(novo == NULL){
        	printf("Erro em: insere_familia.\nRetorno NULL.\n");
        	exit(1);
		} 
        (*prim) = novo;
        return (*prim);
    }else{  
        Familia *aux = (*prim);
        while(aux->prox != NULL){
            aux=aux->prox;   
        }   
        if(novo == NULL) return NULL;
        aux->prox=novo;
    }
    cont->tam = (cont->tam) + 1;
}

Familia *liga_familias(Familia *prim, char *f1, char *f2){
	if(strcmp(f1, f2) == 0){
		printf("Erro em: liga_familias.\nNome igual das familias NULL\n");
		exit(1);
	}
    Familia *aux1 = buscaFamilia(prim, f1);
    Familia *aux2 = buscaFamilia(prim, f2);
    Familia *copia1 = copiaFamilia(aux2);
    Familia *copia2 = copiaFamilia(aux1);
	if(aux1 == NULL || aux2 == NULL || copia1 == NULL || copia2 == NULL){
		printf("Erro em: liga_familias.\nRetorno NULL\n");
		exit(1);
	}
    if(prim == NULL){
        printf("Erro em: liga_familias.\nLista de familias vazia\n");
        exit(1);
    }
    if(aux1->lig == NULL){
        aux1->lig = copia1;
        copia1->ant = aux1;
    } else {
        while(aux1->lig != NULL){
            aux1 = aux1->lig;
        }
        aux1->lig = copia1;
    	copia1->ant = aux1;
	}
    
    if(aux2->lig == NULL){
        aux2->lig = copia2;
        copia2->ant = aux2;
    } else {
        while(aux2->lig != NULL){
            aux2 = aux2->lig;
        }
        
        aux2->lig = copia2;
        copia2->ant = aux2;
    }
}

void insere_virus(Familia *prim, char *nome, int movimento){
	Familia *novo = buscaFamilia(prim, nome);
	Virus *vAux = NULL;
	Virus *virus = alocaVirus(movimento);
	
	if(novo == NULL){
		printf("Erro em: insere_virus.\nLista de familias vazia\n");
		exit(1);
	}
	if(virus == NULL) return;
	
	novo->infectada = 1;

	while(novo->lig != NULL){
		novo = novo->lig;
	}
	if(novo->vLig == NULL){
		novo->vLig = virus;
		virus->fAnt = novo;
	}else{
		vAux = novo->vLig;
		while(vAux->prox != NULL){      //HORIZONTAL
			vAux=vAux->prox;
		}
		vAux->prox = virus;
		virus->vAnt = vAux;
	}
}

void virus_move(Virus *virus, Familia *prim){
	Virus *novoVirus = virus, *virusAux = NULL, *viruzinho = NULL;
	Familia *novo = prim, *familiaAux = NULL, *familia = NULL;
	
	if(virus == NULL && prim == NULL){
		printf("Erro em: virus_move.\nUso incorreto da funcao (Ambos parametros nulos).\n");
        exit(1);
	}
	
	int i, qtd = novo->tam;
	int aux = rand() % qtd;
	
	if(novoVirus->fAnt != NULL){
		//Tem uma familia como anterior;
		familiaAux = novoVirus->fAnt; //familiaAux olhando para o anterior do novoVirus;
		viruzinho = copiaVirus(novoVirus); //uma variavel recebe a funcao copia virus
		RemoveVirus(familiaAux, NULL);
		//=====================================================
		for(i = 0; i<aux; i++){     //Percorre a lista das familias ao inverso;
			if(familiaAux->ant != NULL) familiaAux = familiaAux->ant;
		}

		familia = buscaFamilia(prim, familiaAux->nome); //Busca na lista vertical a familia que foi escolhida;
		insere_virus(prim, familia->nome, (viruzinho->mov)+1);
	}else{
		virusAux = novoVirus->vAnt; //virusAUX aponta para o anterior;
		viruzinho = copiaVirus(novoVirus); //uma variavel recebe a funcao copia virus
		
		RemoveVirus(NULL, virusAux);
		
		while(virusAux->vAnt != NULL){     //Voltar a lista ate o primeiro Virus depois das ligacoes;
	        virusAux = virusAux->vAnt;
	    }
	    familia = virusAux->fAnt;
	    
		for(i = 0; i<aux; i++){     //Percorre a lista das familias ao inverso;
	        if(familia->ant != NULL) familia = familia->ant;
		}
		
		familiaAux = buscaFamilia(prim, familia->nome); //Busca na lista vertical a familia que foi escolhida;
		insere_virus(prim, familiaAux->nome, (viruzinho->mov)+1);
	}
	
}

void virus_multiplica(Familia *prim, Virus *virus){
	Virus *virusAux = virus;
	Familia *familia = NULL;
	if(virus == NULL){
		printf("Erro em: virus_multiplica.\nVirus passado é nulo.\n");
        exit(1);
	}if(prim == NULL){
		printf("Erro em: virus_multiplica.\nFamilia passada é nula.\n");
        exit(1);
	}
	
	
	while(virusAux->vAnt != NULL){     //Voltar a lista ate o primeiro Virus depois das ligacoes;
        virusAux = virusAux->vAnt;	   //Volta a parte dos virus
    }
    familia = virusAux->fAnt;
    
    while(familia->ant != NULL){	//Volta a parte das familias para encontrar a primeira familia da lista.
    	familia = familia->ant;
	}
	insere_virus(prim, familia->nome, 0);
	insere_virus(prim, familia->nome, 0);
}

void agente_saude(Familia *prim){
	if(prim == NULL){
		printf("Erro em: agente_saude.\nTermo passado é nulo.\n");
        exit(1);
	}
	Familia *curada = prim;
	if(curada->infectada == 1) curada->infectada = 2;
}

void agente_atua(Familia *prim, Status *status){
	Familia *familia = prim;
	if(prim == NULL){
		printf("Erro em: agente_atua.\nFamilia é nula.\n");
		exit(1);
	}if(status == NULL){
		printf("Erro em: agente_atua.\nStatus é nulo.\n");
		exit(1);
	}
	
	Status *sts = status;
	int tam = familia->tam;
	int aux = rand() % tam, i;
	
	for(i = 0; i<aux; i++){
		if(familia->prox != NULL) familia = familia->prox;
	}
	agente_saude(familia);
	
	while(familia->lig != NULL){
		familia = familia->lig;
	}
	if(familia->vLig != NULL){
		while(familia->vLig != NULL){
			RemoveVirus(familia, NULL);
		}
		sts->acertos = sts->acertos + 1;
	}else{
		sts->erros = sts->erros + 1;
	}
}

int verifica_surto(Familia *prim){
    Familia *familia = prim;
    if(prim == NULL){
		printf("Erro em: verifica_surto.\nFamilia é nula.\n");
		exit(1);
	}

    int qtdFamilias = familia->tam;
    int numInfectados = calculaInfectados(familia);
    int oitentaPct = calculaOitentaPorcento(qtdFamilias);

	FILE *pont_arq;
    pont_arq = fopen("log.txt", "w");

    if(numInfectados >= oitentaPct){
		return 1;
    }
    return 0;
    
    fclose(pont_arq);
}

int inicia_simulacao(Familia *prim, int vezes, int movAgenteAtua, int movMultiplica, Status *status){
    Familia *familia = prim, *familiaAux = NULL, *familiaPrim = prim;
    Virus *virus = NULL, *virusAux = NULL;
    srand(time(NULL));
    Status *retS = status;
    int i = 0, f, mov = 0, movAntigo = 0, statusTemporario = 0, statusFinal = 0, statusRetorno = 0;
    if(prim == NULL){
    	printf("Erro em: inicia_simulacao.\nFamilia passada é nula.\n");
    	return -1;
	}if(status == NULL){
		printf("Erro em: inicia_simulacao.\nStatus é nulo.\n");
		return -1;
	}if(vezes <= 0 || movAgenteAtua <= 0 || movMultiplica <= 0){
		printf("Erro em: inicia_simulacao.\nParametro(s) negativo(s).\n");
		return -1;
	}
    
    for(i = 0; i<vezes; i++){ //faz o numero de vezes pedido
    	familia = prim;
		familiaAux = NULL;
		familiaPrim = prim;
    	virus = NULL;
    	virusAux = NULL;
    	while(familia != NULL){	//percorrer vertical
    		familiaAux = familia->lig;

    		while(familiaAux->lig != NULL){ //percorre horizontal
    			familiaAux = familiaAux->lig;
			}
			int numeroV = NumeroV(familiaAux);
		
    		for(f = 0; f<numeroV; f++){	
    			virusAux = familiaAux->vLig;
    			if(familiaAux->vLig == NULL){
    				break;	
				}if((virusAux->mov != 0) && (virusAux->mov % movMultiplica == 0)){
    				virus_multiplica(familiaPrim, virusAux);
    				
				}if((mov != 0) && (mov % movAgenteAtua == 0)){
					if(movAntigo != mov){
    					agente_atua(familiaPrim, status);	
					}
					movAntigo = mov;
					
				}if(familiaAux->vLig != NULL){
					virus_move(familiaAux->vLig, familiaPrim);
					mov++;	
				}	
			}
		statusTemporario = verifica_surto(prim);
		
		if(statusTemporario == 1){
			statusRetorno = 1;
		}
		
		if(calculaVirusFinais(prim) == 0){
    		if(statusTemporario == 1){
    			retS->retorno = 2;
			}else{
				if(statusRetorno == 1){
					retS->retorno = 1;
				}else{
					retS->retorno = 0;
				}
			}
    		return mov;
		}
		
		familia = familia->prox;
		}
		familia = familiaPrim;
	}
	
	if(statusTemporario == 1){
    	retS->retorno = 2;
	}else{
		if(statusRetorno == 1){
			retS->retorno = 1;
		}else{
			retS->retorno = 0;
		}
	}
	return mov;
}
