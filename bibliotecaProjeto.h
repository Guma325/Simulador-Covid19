#define bibliotecaProjeto_h

typedef struct virus{
	int mov;
    int qtd;
	struct familia *fAnt;
	struct virus *prox;
	struct virus *vAnt;
}Virus;

typedef struct familia {
    char *nome;
    int qntdPessoas;
    int infectada;
    int tam;

    struct familia *prox;
    struct familia *ant;
    struct familia *lig;
	struct virus *vLig;
} Familia;

typedef struct status{
	int retorno;
	int acertos;
	int erros;
	
}Status;

Familia *insere_familia(Familia **cabeca, char *nome, int qtdP);
Familia *liga_familias(Familia *prim, char *f1, char *f2);

void insere_virus(Familia *prim, char *nome, int movimento);
void virus_multiplica(Familia *prim, Virus *virus);

void agente_atua(Familia *prim, Status *status);
int verifica_surto(Familia *familia);
int inicia_simulacao(Familia *familia, int vezes, int movAgenteAtua, int movMultiplica, Status *status);

