#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecaProjeto.h"
#include "bibliotecaAuxiliar.h"
#include <time.h>

//Made by: github.com/Guma325 & github.com/Skyerv


//Programa feito no Windows utilizando DEV C++ e Visual Studio Code;
//Caso o programa retorne um erro na primeira compilacao,
//descobrimos que é porque cada compilador interpreta as strings linhas (71) e (82)
//de forma distinta. Se utilizar o Linux para compilar e acontecer
//este erro, basta trocar o "-1" por "-2"; 

int main(){
    Familia *familia = NULL;
	FILE *file;
	file = fopen("entrada.txt", "r");
    
	if(file == NULL){
		printf("Nao foi possivel abrir o arquivo");
		return 0;
	}

	char frase[100], *frase2 = NULL, *frase3 = NULL, *aux2 = NULL, aux3[10];
	char *pedaco = NULL;
	int x[4], i=0, qtdVirusInicial=0, contV=0, numeroDeMovimentos = 0;
	Status *status = alocaStatus();
	
	while(fgets(frase, 100, file) != NULL){
		pedaco = strtok(frase, " ");
		while(pedaco != NULL){
			if(strcmp(pedaco, "agente_atua") == 0){
				pedaco = strtok(NULL, " ");
				
				x[0] = atoi(pedaco);

				if(x[0] <= 0){
                    printf("Erro em: agente_atua\nColoque um numero positivo como parametro.\n");
                    return 0;
                }
			}
			if(strcmp(pedaco, "virus_multiplica") == 0){
				pedaco = strtok(NULL, " ");
				x[1] = atoi(pedaco);

				if(x[1] <= 0){
                    printf("Erro em: virus_multiplica\nColoque um numero positivo como parametro.\n");
                    return 0;
                }
			}
			if(strcmp(pedaco, "inserefamilia") == 0){
				pedaco = strtok(NULL, " ");
				frase2 = pedaco;
				pedaco = strtok(NULL, " ");
				x[2] = atoi(pedaco);
				
				if(x[2] <= 0){
                    printf("Erro em: inserefamilia\nColoque um numero positivo para o numero de integrantes da familia.\n");
                    return 0;
                }
				insere_familia(&familia,frase2,x[2]);
			}
			if(strcmp(pedaco, "ligafamilias") == 0){
				pedaco = strtok(NULL, " ");
				frase2 = pedaco;
				pedaco = strtok(NULL, " ");
				frase3 = pedaco;
				
				for(i=0;i<=(strlen(pedaco)-1);i++){
					aux3[i] = pedaco[i];
					if(i == strlen(pedaco)-1){   
						aux3[i] = '\0';
					}
				}
				liga_familias(familia, frase2, aux3);
			}
			
			if(strcmp(pedaco, "inserevirus") == 0){
				pedaco = strtok(NULL, " ");
				for(i=0;i<=(strlen(pedaco)-1);i++){
					aux3[i] = pedaco[i];
					if(i == strlen(pedaco)-1){
						aux3[i] = '\0';
					}
				}

				frase2 = pedaco;
				insere_virus(familia, aux3, 0);
				qtdVirusInicial++;
			}
			if(strcmp(pedaco, "iniciasimulacao") == 0){
				pedaco = strtok(NULL, " ");
				x[3] = atoi(pedaco);
				
				numeroDeMovimentos = inicia_simulacao(familia, x[3], x[0], x[1], status);
				if(numeroDeMovimentos < 0){
					exit(1);
				}
				
				if(x[3] <= 0){
                    printf("Erro em: iniciasimulacao\nColoque um numero positivo como parametro.\n");
                    return 0;
                }
			}
			if(strcmp(pedaco, "verificasurto") == 0){
				verifica_surto(familia);
			}
			
			pedaco = strtok(NULL, " ");
		}
	}
	contV = calculaVirusFinais(familia);
	
	printf("Estado Final da simulacao:\n");
	imprimeLista(familia);
	/*statusRetorno == 0, Nao houve surto; 
	statusRetorno == 1, Houve surto, mas foi controlado
	statusRetorno == 2, Houve surto, mas nao foi controlado*/

	FILE *pont_arq;
    pont_arq = fopen("log.txt", "w");
    
	if(status->retorno == 0){
		fprintf(pont_arq,"Nao houve surto\n");
	}else if(status->retorno == 1){
		fprintf(pont_arq,"Houve surto, mas foi controlado\n");
	}else if(status->retorno == 2){
		fprintf(pont_arq,"Houve surto, mas nao foi controlado\n");
	}
	fprintf(pont_arq,"Numero de movimentos totais dos virus: %d\n", numeroDeMovimentos);
	fprintf(pont_arq,"virus iniciais: %d\n", qtdVirusInicial);
	fprintf(pont_arq,"virus finais: %d\n", contV);
	fprintf(pont_arq,"Acertos do Agente: %d\n", status->acertos);
	fprintf(pont_arq,"Erros do Agente: %d\n", status->erros);
    fclose(pont_arq);
    
	fclose(file);
	return 0;
}
