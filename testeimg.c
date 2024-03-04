#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int** novaMatriz = malloc(sizeof(int*) * arquivo->numeroLinhas);
    
    int tamanho = arquivo->numeroColunas;
    for (int i = 0; i < arquivo->numeroLinhas; i++){
        novaMatriz[i] = malloc(sizeof(int) * tamanho);
        // int* novoVetor[tamanho];
    }
    

    int k;

    for (k = 0; k < arquivo->numeroLinhas; k++){

        int i = 0, j = 0, novoTamanhoColunas = 0;
        int contaRepeticao = 1;

        for (j = i + 1; j < tamanho; j++) {
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

int** preencheMatrizCompactada(FILE* arquivo, Arquivo* novoArquivo){
    for (int i = 0; i < novoArquivo->numeroLinhas; i++){
        char prototipo;
        for (int j = 0; j < novoArquivo->numeroColunas; j++){ 

            fscanf(arquivo,"%c",&prototipo);
            if (prototipo == '@')
            {
                novoArquivo->matriz[i][j] =  prototipo;
            }
    
            fscanf(arquivo,"%d",&novoArquivo->matriz[i][j]);
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
        printf("DEU BOM!\n");
        preencheMatrizDesconpactada(arquivo,novoArquivo);
    }
    else{
        printf("DEU RUIM!\n");
    }

    if(strcmp(novoArquivo->nome,"P2") == 0){
        compactaMatriz(novoArquivo);
    }
    printMatriz(novoArquivo);
    // else Descompactar(arquivo);
    return novoArquivo;
        
}

int main(){
    FILE* arquivo;
    arquivo = abrirArquivo("exemplo1.pgm");
    Arquivo *novoArquivo;
    novoArquivo = lerArquivo(arquivo);
    // *novoArquivo = transformaArquivo(novoArquivo);
    // escreveArquivo(novoArquivo);
}