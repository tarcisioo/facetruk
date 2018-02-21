                /// Tarcísio de Oliveira Rocha

#include "myface.h"

///funções do TAD TipoLista
void FLVazia(TipoLista *Lista){// cria uma lista vazia
  Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista){// testa se a lista esta vazia
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista){// insere um novo elemento a lista
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista , TipoItem *Item){// retira um elemento da lista
    //O item a ser retirado e o seguinte ao apontado por p
    TipoApontador q;
    if (Vazia(*Lista)||p==NULL||p->Prox==NULL){
        printf("\nErro : Lista vazia ou posicao nao existe \n");
        return;
    }

    q = p->Prox;
    *Item = q->Item ;
    p->Prox = q->Prox;
    if(p->Prox == NULL)Lista->Ultimo = p;
    free(q);
}

void Imprime(TipoLista Lista){// imprime toda a lista
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    printf("\nLista de amigos: ");
    while (Aux!=NULL){
      printf("%d,",Aux->Item.ID_amigo);
      Aux = Aux->Prox;
    }
    printf("\n");
}

/// funções TAD usuario

int procura_usuario(usuario A[],int tamanho,int ID){// essa função foi criada para retornar a posição do usuario com o identificador ID

    int i;
    for(i=0;i<tamanho;i++){
        if(ID==A[i].ID){
            return i;
        }//fim if
    }//fim for
    return -1;
}//fim

int procura_mensagem(mensagem A[],int indice,int ID){// essa função retorna a posição onde se econtra a menmsagem procurada
    int i;
    for(i=0;i<indice;i++){
        if(ID==A[i].ID_mensagem){
            return i;

        }//fim if
    }//fim for
    return -1;
}//fim

TipoApontador procura_amigo(TipoLista *L,TipoItem item){// retorna o apontador que aponta para o amigo procurado

    TipoApontador aux = L->Primeiro;

    while(aux!=NULL){// enquando nãochegar ao fim

        if(aux->Prox->Item.ID_amigo==item.ID_amigo){

            return aux;
        }
        aux = aux->Prox;// ir para a proxima celula
    }//fim while

    return 0;
}

int postarMensagem(mensagem post,usuario *A,int tamanho,int user){

    TipoApontador aux =A[user].amigos.Primeiro;
    int i,k,ID;
    ID = A[user].ID;
    i = procura_usuario(A,tamanho,ID);
    strcpy(A[user].LT[A[user].indice].text,post.texto);
    A[user].LT[A[user].indice].ID_msg = post.ID_mensagem;
    A[user].indice++;

    while (aux->Prox!=NULL){
        ID = aux->Prox->Item.ID_amigo;
        i = procura_usuario(A,tamanho,ID);

        strcpy(A[i].LT[A[i].indice].text,post.texto);
        A[i].LT[A[i].indice].ID_msg = post.ID_mensagem;
        aux = aux->Prox;
        A[i].indice++;
    }

    return 1;
}

int iniciarAmizade(usuario *A,TipoItem x){

    Insere(x,&A->amigos);
    return 1;
}

int cancelarAmizade(usuario *A,TipoItem Item){

    TipoApontador p  = procura_amigo(&A->amigos,Item);
    Retira(p,&A->amigos,&Item);

    return 1;
}

int curtirMensagem(int tempo,mensagem A[],int indice,int ID_User, int ID_mensagem){

    int i = procura_mensagem(A,indice,ID_mensagem);

    A[i].curtidas++;
    A[i].t = tempo;

    return 1;
}

int exibirTimeline(FILE *saida, timeline LT[], int indice,int tempo, int ID_usuario){

    int i;
    for(i=indice-1;i>=0;i--){
        fprintf(saida,"%d %d %d %s\n",tempo,ID_usuario,LT[i].ID_msg,LT[i].text);
    }
    return 1;
}

int verAmigos(TipoLista L){
    Imprime(L);

    return 1;
}
