#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* nome;
    int numeroColunas, numeroLinhas, maiorPixel;
    char** matriz;
} Arquivo;

char** criaMatrizDinamica(int numeroLinhas, int numeroColunas){
    char** matriz = (char**) malloc(sizeof(char**) * numeroLinhas + 1);
    for (int i = 0; i < numeroLinhas; i++){
        matriz[i] = (char*) malloc(sizeof(char*) * numeroColunas + 1);
    }
    return matriz;
}

char* escreverArquivo(Arquivo *arquivoEntrada, FILE *arquivoSaida){
    arquivo = ("saida.pgmc", "w");

    fprintf(arquivo, )
    
    
    fprintf("%d %d", arquivoEntrada->numeroColunas, arquivoEntrada->numeroLinhas);
    
}

char* descompactarArquivo(Arquivo *arquivoEntrada, FILE *arquivoSaida){
    arquivo = ("saida.pgm", "w");

    char **novaMatriz = criaMatrizDinamica(arquivoEntrada->numeroLinhas, arquivoEntrada->numeroColunas);
    
    for(int i = 0; i < arquivoEntrada->numeroLinhas; i++){
        for(int j = 0; j < arquivoEntrada->numeroColunas; j++){
            if(arquivoEntrada->matriz[i][j] == "@"){
                for(int k = 0; k < arquivoEntrada->matriz[i][j+4]){
                    novaMatriz[i][j + k] = arquivoEntrada->matriz[i][j+2];
                }
            } else {
                novaMatriz[i][j] = arquivoEntrada->matriz[i][j];
            }
        }
    }

    return novaMatriz;

}

Arquivo* lerArquivo(FILE* arquivo){
    printf("passou");
    Arquivo *novoArquivo = (Arquivo*) malloc(sizeof(Arquivo) * 1);

    fscanf(arquivo,"%s", novoArquivo->nome);
    fscanf(arquivo, "%d %d", &novoArquivo->numeroColunas, &novoArquivo->numeroLinhas);
    fscanf(arquivo, "%d", &novoArquivo->maiorPixel);

    novoArquivo->matriz = criaMatrizDinamica(novoArquivo->numeroLinhas, novoArquivo->numeroColunas);
    
    //Preenche Matriz;
    for (int i = 0; i < novoArquivo->numeroLinhas; i++){
        for (int j = 0; j < novoArquivo->numeroColunas; j++)
        {
            fscanf(arquivo,"%c", &novoArquivo->matriz[i][j]);
        }
        
    }
    
    printf("%s\n", novoArquivo->nome);
    printf("%d %d\n",novoArquivo->numeroColunas,novoArquivo->numeroLinhas); // teste
    // printMatriz(novoArquivo->matriz,novoArquivo->numeroLinhas,novoArquivo->numeroColunas);
    
    // if(novoArquivo->nome == "P2")Compactar(arquivo);
    // else Descompactar(arquivo);
    if(arquivo == NULL) {
        printf("Erro na leitura");
    }

    return novoArquivo;
        
}

int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Uso: %s arquivo_entrada arquivo_saida\n", argv[0]);
        return 1;
    }

    FILE* arquivoEntrada;
    FILE* arquivoSaida;
    arquivoEntrada = fopen("exemplo1.pgm", "r");
    arquivoSaida = fopen("saida.pgmc", "w");

    Arquivo *novoArquivo;
    novoArquivo = lerArquivo(arquivoEntrada);
    

}




