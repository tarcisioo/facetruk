                    /// Tarcísio de Oliveira Rocha

#include <stdio.h>
#include <stdlib.h>

#define TWEETS 140//dado do enunciado
#define MAX_AMIGOS 5000//numero de amigos, mesmo numero que do facebook
#define MAX_NOME 50//tamanho maximo do nome do usuario
#define MSG_TAM 1000// tamanho da mensagem
#define TIMELINE_MAX 1000// tamanho maximo para timeline

///codigos
#define POSTAR_MENSAGEM 1
#define INICIAR_AMIZADE 2
#define CANCELAR_AMIZADE 3
#define CURTIR_MENSAGEM 4
#define EXIBIR_TIMELINE 5

typedef int TipoChave;
typedef struct TipoItem{
    TipoChave ID_amigo;// a unica modificação da ista vista em sala de aula, no lugar de chave entra ID_amigo
}TipoItem;

typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula{
    TipoItem Item;
    TipoApontador Prox;
}TipoCelula;

typedef struct TipoLista{
    TipoApontador Primeiro,Ultimo;
}TipoLista;

typedef struct mensagem{
    int ID_mensagem;// identificador da mensagem
    char texto[TWEETS];//tamanho maximo da mensagem
    int t; // instante em que foi postada
    int curtidas;//numero de curtidas
    int ID_user;// ID do usuario em questão
}mensagem;

typedef struct timeline{
    char text[TWEETS];// mensagem contida na timeline
    int ID_msg;// identificador dessa mensagem
}timeline;

typedef struct usuario{
    int ID;// identificador do usuario
    char nome[MAX_NOME];//nome do usuario
    TipoLista amigos;// lista de amigos do usuario
    timeline LT[TIMELINE_MAX];// vetor para mensagens contidas na timeline desse usuario
    int indice;// esse indice contem a posição do ultimo elemento valido de LT
}usuario;




