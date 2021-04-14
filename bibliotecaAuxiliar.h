#define bibliotecaAuxiliar_h

Familia *alocaFamilia(char *nome, int qtdP);
Familia *buscaFamilia(Familia *prim, char *nome);
Familia *copiaFamilia(Familia *copiada);

Virus *alocaVirus(int mov);
Virus *copiaVirus(Virus *copiado);
void virus_move(Virus *virus, Familia *prim);
void RemoveVirus(Familia *fAnterior, Virus *vAnterior);

Status *alocaStatus();

int calculaInfectados(Familia *prim);
int calculaOitentaPorcento(int qtd);
int NumeroV(Familia *familia);
int calculaVirusFinais(Familia *familia);

void agente_saude(Familia *prim);
void imprimeLista(Familia *cabeca);


//void free_lista();
