#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char nome[10];
    int numeroColunas, numeroLinhas, maiorPixel;
    int** matriz;
} Arquivo;

void printMatriz(Arquivo* arquivo){
    for (int i = 0; i < arquivo->numeroLinhas; i++){
        int j = 0;
        while(arquivo->matriz[i][j] != -2){
            if (arquivo->matriz[i][j] == -1){printf("@ ");}
            else{
                printf("%d ",arquivo->matriz[i][j]);
            }
            j++;
        }
        printf("\n");
    }
    
}

int** criaMatrizDinamica(int numeroLinhas,int numeroColunas){
    int** matriz;
    matriz = (int**) malloc(sizeof(int*) * numeroLinhas);
    for (int i = 0; i < numeroLinhas; i++){
        matriz[i] = malloc(sizeof(int) * numeroColunas);
    }
    return matriz;
}

void preencheMatrizDesconpactada(FILE* arquivo,Arquivo* novoArquivo){
    for (int i = 0; i < novoArquivo->numeroLinhas; i++){
        for (int j = 0; j < novoArquivo->numeroColunas; j++){   
            fscanf(arquivo,"%d",&novoArquivo->matriz[i][j]);
        }
    }
}

void limpaMatrizDoArquivo(Arquivo* arquivo){
    for (int i = 0; i < arquivo->numeroLinhas; i++){
        free(arquivo->matriz[i]);
    }
    free(arquivo->matriz);
}

int compactaMatriz(Arquivo* arquivo){
    int** novaMatriz = criaMatrizDinamica(arquivo->numeroLinhas,arquivo->numeroColunas);
    
    for (int k = 0; k < arquivo->numeroLinhas; k++){

        int i = 0, j = 0, novoTamanhoColunas = 0;
        int contaRepeticao = 1;

        for (j = i + 1; j < arquivo->numeroColunas; j++) {
            if (arquivo->matriz[k][i] == arquivo->matriz[k][j]) {
                contaRepeticao++;
            } else {
                if (contaRepeticao >= 3) {
                    novaMatriz[k][novoTamanhoColunas++] = -1;
                    novaMatriz[k][novoTamanhoColunas++] = arquivo->matriz[k][i];
                    novaMatriz[k][novoTamanhoColunas++] = contaRepeticao;
                } else {
                    for (int l = 0; l < contaRepeticao; l++) {
                        novaMatriz[k][novoTamanhoColunas++] = arquivo->matriz[k][i];
                    }
                }
                contaRepeticao = 1;
                i = j;
            }
        }
        if (contaRepeticao >= 3) {
            novaMatriz[k][novoTamanhoColunas++] = -1;
            novaMatriz[k][novoTamanhoColunas++] = arquivo->matriz[k][i];
            novaMatriz[k][novoTamanhoColunas++] = contaRepeticao;
        } else {
            for (int l = 0; l < contaRepeticao; l++) {
                novaMatriz[k][novoTamanhoColunas++] = arquivo->matriz[k][i];
            }
        }
        novaMatriz[k][novoTamanhoColunas] = -2;
    }

    limpaMatrizDoArquivo (arquivo);

    arquivo->matriz = novaMatriz;
    return 1;
}

int descompactaMatriz(Arquivo* arquivo){
    int tamanho = arquivo->numeroColunas;

    for (int k = 0; k < arquivo->numeroLinhas; k++){
        for (int i = 0; i < tamanho; i++){
            if (arquivo->matriz[k][i] == -1){
                int repetido = arquivo->matriz[k][i+1];
                int quantidade = arquivo->matriz[k][i+2];

                for (int j = i; j < quantidade + i; j++){
                    arquivo->matriz[k][j] = repetido;            
                }
            }
            else{
                arquivo->matriz[k][i] = arquivo->matriz[k][i]; 
            }
        }
    }
    // printMatriz(arquivo);
    return 1;
}

void preencheMatrizCompactada(FILE* arquivo, Arquivo* novoArquivo){
    char* linha;
    linha = (char * ) malloc(sizeof(char) * novoArquivo->numeroColunas*4);
    int tamanho = novoArquivo->numeroColunas*2+4;
    char separador[2] = " ";
    char* token;

    for(int i = 0; i < novoArquivo->numeroLinhas+1; i++){
        fgets(linha, tamanho, arquivo);
        if (i>0){ 
            printf("Linha lida antes: %s",linha);
            token = strtok(linha,separador);
            int j = 0;
            while (token != NULL){
                printf("token: %s\n",token);
                if (strcmp(token,"@") ==  0){
                    novoArquivo->matriz[i][j] = -1;
                }
                else{
                    novoArquivo->matriz[i][j] = atoi(token);
                }
                printf("adicionado na matriz: %d\n",novoArquivo->matriz[i][j]);
                token = strtok(NULL,separador);
                j++;
            }
            
        }  
    }
}

FILE* abrirArquivo(char* nomeArquivo){
    FILE* arquivo;
    arquivo = fopen(nomeArquivo, "r");
    return arquivo;
}

Arquivo* lerArquivo(FILE* arquivo){
    if(arquivo == NULL) printf("Erro na leitura");
    
    Arquivo *novoArquivo = (Arquivo*) malloc(sizeof(Arquivo) * 1);
    fscanf(arquivo,"%s", &novoArquivo->nome);
    printf("%s\n",novoArquivo->nome);
    fscanf(arquivo, "%d %d", &novoArquivo->numeroColunas, &novoArquivo->numeroLinhas);
    fscanf(arquivo, "%d", &novoArquivo->maiorPixel);

    novoArquivo->matriz = criaMatrizDinamica(novoArquivo->numeroLinhas,novoArquivo->numeroColunas);
    if (strcmp(novoArquivo->nome,"P2") == 0){  
        printf("Compactando...\n");
        preencheMatrizDesconpactada(arquivo,novoArquivo);
        compactaMatriz(novoArquivo);
    }
    else{
        printf("Descompactando...\n");
        preencheMatrizCompactada(arquivo,novoArquivo);
        descompactaMatriz(novoArquivo);
    }
    // printMatriz(novoArquivo);
    return novoArquivo;
}

void escreverArquivo(Arquivo *arquivo, FILE *arquivoSaida){
    if(strcmp(arquivo->nome,"P2") == 0) fprintf(arquivoSaida,"P8 \n");
    else fprintf(arquivoSaida, "%s \n",arquivo->nome);

    fprintf(arquivoSaida,"%d %d \n", arquivo->numeroColunas, arquivo->numeroLinhas);
    fprintf(arquivoSaida, "%d \n", arquivo->maiorPixel);

    for(int i = 0; i < arquivo->numeroLinhas; i++){
        int j = 0;
        while(arquivo->matriz[i][j] != -2){
            if (arquivo->matriz[i][j] == -1){
                fprintf(arquivoSaida,"@ ");
            }
            else{
                fprintf(arquivoSaida,"%d ",arquivo->matriz[i][j]);
            }
            j++;
        }
        fprintf(arquivoSaida,"\n");
    }
}

int main(int argc, char* argv[]){
    // TESTE GIT
    if (argc != 3) {
        printf("Uso: %s arquivo_entrada arquivo_saida\n", argv[0]);
        return 1;
    }

    FILE* arquivoEntrada = fopen(argv[1], "r");
    FILE* arquivoSaida = fopen(argv[2], "w");

    if (arquivoEntrada == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    Arquivo *novoArquivo;
    novoArquivo = lerArquivo(arquivoEntrada);
    escreverArquivo(novoArquivo,arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);
}