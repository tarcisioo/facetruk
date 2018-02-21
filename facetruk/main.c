                   /// Tarcísio de Oliveira Rocha

#include "myface.h"

int main()/// aqui devo implementar como arquivo de entrada vai ser recebido, em caso de uma entrada do tipo entrada0001.txt  a saida deverá ser log0001.txt
{
    FILE *entrada,*saida;
    entrada = fopen("entrada.txt","r");
    saida = fopen("log.txt","w");

    int numero_de_usuarios;
    fscanf(entrada,"%d",&numero_de_usuarios);//obtem numero de usuarios

    int ID_do_usuario1,ID_do_usuario2;
    int ID_mensagem;
    char nome[MAX_NOME];
    char p_e_v;
    char msg[TWEETS];
    int x,y,z;
    TipoItem item;
    usuario A[numero_de_usuarios];

    int j;
    for(j=0;j<numero_de_usuarios;j++){//inicializando o indice de todos os usuarios
        A[j].indice=0;
    }// fim do for

    int indice_messagem = 0;
    mensagem frase[MSG_TAM];

/// PARTE I -> feito
    int i;
    for(i=0;i<numero_de_usuarios;i++){

        FLVazia(&A[i].amigos);
        fscanf(entrada,"%d%c%[^;]",&ID_do_usuario1,&p_e_v,nome);

        A[i].ID = ID_do_usuario1; //grava id do usuario e seu nome
        strcpy(A[i].nome,nome);

        fscanf(entrada,"%c",&p_e_v);
        while(p_e_v==';'){
            fscanf(entrada,"%d",&item.ID_amigo);//coleta amigo
            iniciarAmizade(&A[i],item);
            fscanf(entrada,"%c",&p_e_v);//incrementa condição para o loop
        }
        printf("\n\n");
    }// fim do for
/// PARTE II Ações
     int tempo;
     int codigo;

     while(feof(entrada)==0)// enquanto o arquivo não termina
    {
        fscanf(entrada,"%d%c%d%c",&tempo,&p_e_v,&codigo,&p_e_v);

        if(codigo==POSTAR_MENSAGEM){
           //postarMensagem(tempo,ID,ID_mensagem,mensagem);//Tempo;Codigo;Usuario;IdMensagem;Texto
           fscanf(entrada,"%d%c%d%c%[^\n]s",&ID_do_usuario1,&p_e_v,&ID_mensagem,&p_e_v,msg);

            // inicializa a mensagem, recebe tempo, mensagem, Id e inicializa curtidas = zero
           frase[indice_messagem].t = tempo;
           strcpy(frase[indice_messagem].texto,msg);
           frase[indice_messagem].ID_mensagem = ID_mensagem;
           frase[indice_messagem].curtidas = 0;
           frase[indice_messagem].ID_user = ID_do_usuario1;
           postarMensagem(frase[indice_messagem],A,numero_de_usuarios,procura_usuario(A,numero_de_usuarios,ID_do_usuario1));
           indice_messagem++;// incrementa a menssagem
        }
        if(codigo==INICIAR_AMIZADE){
            fscanf(entrada,"%d%c%d",&ID_do_usuario1,&p_e_v,&item.ID_amigo);
            int user = procura_usuario(A,numero_de_usuarios,ID_do_usuario1);
            if(user!= -1){
                iniciarAmizade(&A[user],item);
            }
           verAmigos(A[user].amigos);
        }
        if(codigo==CANCELAR_AMIZADE){
            //cancelarAmizade(ID);//Tempo;Codigo;Usuario1;Usuario2
            fscanf(entrada,"%d%c%d",&ID_do_usuario1,&p_e_v,&ID_do_usuario2);
            int k;
            k = procura_usuario(A,numero_de_usuarios,ID_do_usuario1);
            TipoItem I;
            I.ID_amigo = ID_do_usuario2;
            cancelarAmizade(A[k],I);
        }
        if(codigo==CURTIR_MENSAGEM){
            //curtirMensagem(tempo,ID;ID_mensagem);//Tempo;Codigo;Usuario;IdMensagem
            fscanf(entrada,"%d%c%d",&ID_do_usuario1,&p_e_v,ID_mensagem);
            curtirMensagem(tempo,frase,indice_messagem,ID_do_usuario1,ID_mensagem);

            /// se é amigo atualiza a mensagem
            int i,j,k;
            timeline aux;
            for(i=0;i<numero_de_usuarios;i++){
                for(j=0;j<A[i].indice;j++){
                    if(ID_mensagem==A[i].LT[j].ID_msg){
                           aux = A[i].LT[j];
                           for(k=j; k < A[i].indice; k++){
                                A[i].LT[k] = A[i].LT[k+1]; // arreda
                           }// fim do for
                           A[i].LT[(A[i].indice-1)] = aux;// coloca por ultimo na fila.
                    }// fim do if
                }//fim do for interno
            }// fim do for
                ///retira e coloca no final
        }// fim do if

        if(codigo==EXIBIR_TIMELINE){
            //exibirTimeline(tempo,ID);//Tempo;Codigo;Usuario
            fscanf(entrada,"%d",&ID_do_usuario1);
            int k = procura_usuario(A,numero_de_usuarios,ID_do_usuario1);
            exibirTimeline(saida,A[k].LT,A[k].indice,tempo,ID_do_usuario1);
        }// fim do if
    }//fim do while

    return 0;
}
