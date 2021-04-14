#include "bibliotecaProjeto.h"
#include "bibliotecaAuxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

Familia *alocaFamilia(char *nome, int qtdP){
    Familia *familia = (Familia *)malloc(sizeof(Familia));
    if(familia == NULL) return NULL;
    familia->nome = strdup(nome);
    familia->infectada = 0;
    familia->qntdPessoas = qtdP;
    familia->prox = NULL;
    familia->ant = NULL;
    familia->lig = NULL;
    familia->vLig = NULL;
    familia->tam = 1;
    return familia;
}

Virus *alocaVirus(int mov){
    Virus *virus = (Virus *)malloc(sizeof(Virus));
    if(virus == NULL) return NULL;
    virus->mov = mov;
    virus->prox = NULL;
    virus->fAnt = NULL;
    virus->vAnt = NULL;
    virus->qtd = 0;
    
	return virus;
}

Status *alocaStatus(){
	Status *status = (Status *) malloc(sizeof(Status));
	if(status == NULL) return NULL;
	status->retorno = 0;
	status->acertos = 0;
	status->erros = 0;
	
	return status;
}

Familia *buscaFamilia(Familia *prim, char *nome){ //Busca vertical
    Familia *novo = prim;
    if(novo == NULL){
		return NULL;
    } else {
        if((strcmp(novo->nome, nome))==0){
            return novo;
        }
        buscaFamilia(novo->prox, nome);
    }
}

Familia *copiaFamilia(Familia *copiada){
    Familia *aux = copiada;
    if(aux == NULL){
        printf("Erro em: copiaFamilia.\nRetorno NULL.\n");
        exit(1);
    }
	Familia *copia = alocaFamilia(aux->nome, aux->qntdPessoas);
	
    
    return copia;
}

Virus *copiaVirus(Virus *copiado){
    Virus *aux = copiado;
    if(aux == NULL){
        printf("Erro em: copiaVirus.\nRetorno NULL.\n");
        exit(1);
    }
	Virus *copia = alocaVirus(aux->mov);
    return copia;
}

void RemoveVirus(Familia *fAnterior, Virus *vAnterior){
	if(fAnterior == NULL && vAnterior == NULL){
		printf("Erro em: RemoveVirus.\nUso incorreto da funcao (Ambos parametros nulos).\n");
        exit(1);
	}
	Virus *lixo = NULL, *proximo = NULL;
	
	if(fAnterior != NULL){
		lixo = fAnterior->vLig;
		if(lixo->prox != NULL){
			proximo = lixo->prox;
			proximo->fAnt = fAnterior;
			proximo->vAnt = NULL;
		} 
		fAnterior->vLig = proximo;

		free(lixo);
		lixo = NULL;
	}else{
		lixo = vAnterior->prox;
		
		if(lixo->prox != NULL){
			proximo = lixo->prox;	
			proximo->vAnt = vAnterior;
		}
		vAnterior->prox = proximo;
		
		free(lixo);
		lixo = NULL;	
	}
}

int NumeroV(Familia *familia){
	Familia *final = familia;
	if(familia == NULL){
    	printf("Erro em: NumeroV.\nFamilia passada é vazia.\n");
    	exit(1);
	}
	
	Virus *aux = NULL;
	int cont = 0;
	
	if(final->vLig != NULL){
		aux = final->vLig;
		while(aux != NULL){
			aux = aux->prox;
			cont++;
		} 
	}
	return cont;
}

int calculaVirusFinais(Familia *prim){
    Familia *familia = prim, *familiaAux = NULL;
    if(familia == NULL){
    	printf("Erro em: calculaVirusFinais.\nLista de familias vazias\n");
    	exit(1);
	}
    int cont=0;
    while(familia != NULL){
    	familiaAux = familia->lig;
    	while(familiaAux->lig != NULL){ //percorre horizontal
    		familiaAux = familiaAux->lig;
		}
        cont = cont + NumeroV(familiaAux);
        familia = familia->prox;
    }
    return cont;
}

int calculaOitentaPorcento(int qtd){
	if(qtd <= 0){
		printf("Erro em: calculaOitentaPorcento.\nParametro negativo\n");
		exit(1);
	}
    int oitentaPct = (80*qtd)/100;
    return oitentaPct;
}

int calculaInfectados(Familia *prim){
    Familia *familia = prim;
    if(familia == NULL){
    	printf("Erro em: calculaInfectados.\nLista de familias vazia\n");
    	exit(1);
	}
    int infectadas = 0;

    if(familia == NULL) return 0;
    while(familia != NULL){
        if(familia->infectada == 1) infectadas++;
        familia = familia->prox;
    }
    return infectadas;
}

void imprimeLista(Familia *prim){
    Familia *novo = prim;
    Familia *aux = NULL;
    Virus *vAux = NULL;
    char *texto;
    int cont = 1;
    if(novo == NULL){
        printf("Lista vazia.\n");
        return;
    }
    while(novo != NULL){
        if(novo->infectada == 0){
            texto = "Limpa";
        } else if (novo->infectada == 1){
            texto = "Infectada";
        } else if (novo->infectada == 2){
            texto = "Curada";
        } else {
            texto = "Desconhecido";
        }
        printf("-> Familia %s | %s\n", novo->nome, texto);
        if(novo->lig != NULL){
            aux = novo;
            printf("Ligada com: ");
            while(aux->lig != NULL){
                if(aux->lig->lig != NULL){
                	printf("%s, ", (aux->lig)->nome);
				}else {
					printf("%s", (aux->lig)->nome);
				}
                aux = aux->lig;
            }
            printf("\n");
            if(aux->vLig != NULL){ //Printa o numero total de virus em cada familia,
								   // caso queira que printe os virus e seus movimentos individuais apenas descomente os comentarios a seguir:
//            	cont = 1;
                int numero = NumeroV(aux);
                printf("Numero de virus na familia: %d\n", numero);
//                vAux = aux->vLig;
//                while(vAux != NULL){
//                    printf("Numero de mov do virus %d: %d\n", cont, vAux->mov);
//                    vAux = vAux->prox;
//                    cont++;
//                }
            }
        }
        printf("--------------------------\n");
        novo = novo->prox;
    }
}

