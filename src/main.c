#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PALAVRAS 50
#define MAX_TAM_PALAVRA 46 //tamanho da maior palavra em pt
#define MAX_ERROS 6

void liberaMatriz(char **m, int l){
    for(int i = 0; i < l; i++){
        free(m[i]);
    }
    free(m);
}

void libera(char **m, int l, int *pJogo, char *dicionario){
    liberaMatriz(m, l);
    free(pJogo);
    free(dicionario);
}

char* alocaPalavra(int tam){
    return (char*)malloc(tam*sizeof(char));
}

int* inicializaVetorPalavra(int tam){
    int *p = (int*)malloc((tam+1)*sizeof(int));
    for(int i = 0; i < tam; i++){
        p[i] = 0;
    }
    return p;
}

char** alocaListaPonteiros(){
    char** m = (char**) malloc(MAX_PALAVRAS * sizeof(char*));
    if(m == NULL){
        printf("Erro ao alocar matriz de ponteiros.");
    }
    return m;
}

char* inicializaDicionario(){
    char* d = (char*)malloc(26*sizeof(char));
    for(char i = 0; i < 26; i++)
        d[i] = '\0';
    return d;
}

int lePalavra(FILE* arq, char* palavra) {
    int tamPalavra = 0;
    char c;
    do{
        c = fgetc(arq);
        palavra[tamPalavra] = c;
        printf(" %c ", palavra[tamPalavra]);
        tamPalavra++;
    }while(c != '\n' && c != EOF);

    palavra[tamPalavra] = '\0';
    printf("%s ", palavra);

    return tamPalavra-1;
}

int escolhePalavra(int numPalavras){
    srand(time(0));
    return rand() % numPalavras;
}

char** leArquivo(int *l) {
    FILE *arq;
    char** m = alocaListaPonteiros();
    int nLinhas = 0;
    arq = fopen("palavras.txt", "r");
    if (arq == NULL) {
        printf("Ocorreu um erro na abertura do arquivo.\n");
        exit(1);
    } else {
        //printf("O arquivo foi aberto com sucesso!\n");
        int coluna = 0, tamPalavra = 0;
        //printf("alocou\n");
        char palavra[MAX_TAM_PALAVRA + 1];
        char c;
        do{
        //for(char c; c != '\n' && c != EOF; c = fgetc(arq)) {
            //printf("entrou no laco\n");
            //c = fgetc(arq);
            //int tamPalavra = lePalavra(arq, palavra);
            do{
                c = fgetc(arq);
                palavra[tamPalavra] = c;
                //printf(" %c ", palavra[tamPalavra]);
                tamPalavra++;
            }while(c != '\n' && c != EOF);

            tamPalavra--;
            palavra[tamPalavra] = '\0';
            
            //printf("%s ", palavra);
            //printf("%d ", tamPalavra);
            m[nLinhas] = (char*) malloc((tamPalavra + 1) * sizeof(char));
            //printf("alocou linha %d da matriz\n", linha);
            if (m[nLinhas] == NULL) {
                printf("Erro ao alocar memória para a palavra.\n");
                exit(1);
            }
            strcpy(m[nLinhas], palavra);
            //printf("%s\n", m[nLinhas]);
            nLinhas++;
            tamPalavra = 0;
        } while(c != EOF);
    }
    fclose(arq);
    *l = nLinhas;
    return m;
}

void imprimeBoneco(int e, int tent){
    printf("\nRodada %d:\n", tent+1);
    switch(e){
        case 0:
            printf("  _________\n  |/      |\n  |\n  |\n  |\n  |\n__|__\n");
            break;
        case 1:
            printf("  _________\n  |/      |\n  |      ( )\n  |\n  |\n  |\n__|__\n");
            break;
        case 2:
            printf("  _________\n  |/      |\n  |      ( )\n  |       |\n  |       |\n  |\n__|__\n");
            break;
        case 3:
            printf("  _________\n  |/      |\n  |      ( )\n  |       |\n  |       |\n  |\n__|__\n");
            break;
        case 4:
            printf("  _________\n  |/      |\n  |      ( )\n  |       |\n  |       |\n  |\n__|__\n");
            break;
        case 5:
            printf("  _________\n  |/      |\n  |      ( )\n  |      /|\\\n  |       |\n  |      / \n__|__\n");
            break;
        case 6:
            printf("  _________\n  |/      |\n  |      ( )\n  |      /|\\\n  |       |\n  |      / \\\n__|__\n");
            break;
        default:
            break;
    }
}

void imprimePalavra(char* p, int *pJogo, int e){
    printf("p = %s\n", p);
    if(e < 6){
        for(int i = 0; p[i] != '\0'; i++){
            if(pJogo[i] == 0)
                printf(" _ ");
            else
                printf("%c", p[i]);
        }
    }
    else 
        printf("Fim de jogo :( A palavra era %s", p);
    printf("\n");
}

int* verificaJogada(char l, char *p, int *pJogo, int *e){
    int flag = 0;
    //printf("varifica jogada\n");
    for(int i = 0; p[i] != '\0'; i++){
        //printf("laco verifica jogada\n");
        if(p[i] == l){
            pJogo[i] = 1;
            flag = 1;
        }
    }
    if(!flag){
        printf("A palavra nao tem a letra %c :(\n", l);
        (*e)++;
    }
    //printf("fim verifica jogada\n");
    return pJogo;
}

int verificaVitoria(int *pJogo, char *p){
    for(int i = 0; p[i] != '\0'; i++){
        if(pJogo[i] == 0){
            return 0;
        }
    }
    return 1;
}

int* registraJogada(char* letras, char *p, int *pJogo, int *e){
    char l;
    int flag = 0;
    printf("Digite uma letra: ");
    scanf(" %c", &l);
    getchar();
    //printf("leu\n");
    for(int i = 0; i < 26; i++){
        //printf("entrou no laco\n");
        if(letras[i] == l){
            printf("Voce ja escolheu a letra %c antes. Tente outra.\n", l);
            flag = 1;
            break;
        }
        else if(letras[i] == '\0'){
            letras[i] = l;
            break;
        }
    }
    //printf("saiu do laco\n");
    if(!flag){
        pJogo = verificaJogada(l, p, pJogo, e);
    }
    //printf("fim registra jogada\n");
    return pJogo;
}

int main() {
    int l, erros = 0, tentativas = 0, fim = 0;
    char **m = leArquivo(&l);
    char *dicionario = inicializaDicionario();
    //printf("%d palavras\n", l);
    int pos = escolhePalavra(l);
    int tam = strlen(m[pos]);
    int *pJogo = inicializaVetorPalavra(tam);
    printf("%s %s\n",m[pos], pJogo);

    do{
        imprimeBoneco(erros, tentativas);
        imprimePalavra(m[pos], pJogo, erros);
        pJogo = registraJogada(dicionario, m[pos], pJogo, &erros);
        fim = verificaVitoria(pJogo, m[pos]);
        tentativas++;
    }while(erros < MAX_ERROS || fim != 1);
    
    libera(m, l, pJogo, dicionario);
    printf("matriz liberada com sucesso");
    return 0;
}