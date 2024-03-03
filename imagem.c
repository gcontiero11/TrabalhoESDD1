#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* nome;
    int numeroColunas, numeroLinhas, maiorPixel;
    int** matriz;
} Arquivo;

int** criaMatrizDinamica(int numeroLinhas, int numeroColunas){
    int** matriz;
    matriz = (int**) malloc(sizeof(int*) * numeroLinhas);
    for (int i = 0; i < numeroLinhas; i++){
        matriz[i] = malloc(sizeof(int) * numeroColunas);
    }
    return matriz;
}

// char* escreverArquivo(Arquivo *arquivoEntrada, FILE *arquivoSaida){
//     arquivo = ("saida.pgmc", "w");

//     fprintf(arquivo, );
    
    
//     fprintf("%d %d", arquivoEntrada->numeroColunas, arquivoEntrada->numeroLinhas);
    
// }

// char* descompactarArquivo(Arquivo *arquivoEntrada, FILE *arquivoSaida){
//     arquivo = ("saida.pgm", "w");

//     char **novaMatriz = criaMatrizDinamica(arquivoEntrada->numeroLinhas, arquivoEntrada->numeroColunas);
    
//     for(int i = 0; i < arquivoEntrada->numeroLinhas; i++){
//         for(int j = 0; j < arquivoEntrada->numeroColunas; j++){
//             if(arquivoEntrada->matriz[i][j] == "@"){
//                 for(int k = 0; k < arquivoEntrada->matriz[i][j+4]){
//                     novaMatriz[i][j + k] = arquivoEntrada->matriz[i][j+2];
//                 }
//             } else {
//                 novaMatriz[i][j] = arquivoEntrada->matriz[i][j];
//             }
//         }
//     }

//     return novaMatriz;

// }

void printMatriz(int** matriz, int numeroLinhas , int numeroColunas){
    for (int i = 0; i < numeroLinhas; i++)
    {
        for (int j = 0; j < numeroColunas; j++)
        {
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    
}

Arquivo* lerArquivo(FILE* arquivo){
    Arquivo *novoArquivo = (Arquivo*) malloc(sizeof(Arquivo) * 1);

    fscanf(arquivo,"%s", novoArquivo->nome);
    fscanf(arquivo, "%d %d", &novoArquivo->numeroColunas, &novoArquivo->numeroLinhas);
    fscanf(arquivo, "%d", &novoArquivo->maiorPixel); 
    printf("%d\n",novoArquivo->numeroLinhas);
    novoArquivo->matriz = criaMatrizDinamica(novoArquivo->numeroLinhas, novoArquivo->numeroColunas);
    
    //Preenche Matriz;
    char prototipo;
    for (int i = 0; i < novoArquivo->numeroLinhas; i++){
        for (int j = 0; j < novoArquivo->numeroColunas; j++)
        {   
            fscanf(arquivo,"%c", &prototipo);
            if (prototipo != ' ')
            {
                novoArquivo->matriz[i][j] = prototipo;
            }
        }
        
    }
    
    printf("%s\n", novoArquivo->nome);
    printf("%d %d\n",novoArquivo->numeroColunas,novoArquivo->numeroLinhas); // teste
    printMatriz(novoArquivo->matriz,novoArquivo->numeroLinhas,novoArquivo->numeroColunas);
    
    // if(novoArquivo->nome == "P2")Compactar(arquivo);
    // else Descompactar(arquivo);
    if(arquivo == NULL) {
        printf("Erro na leitura");
    }

    return novoArquivo;
        
}
// int argc, char *argv[]
int main(){
    // if (argc != 3) {
    //     printf("Uso: %s arquivo_entrada arquivo_saida\n", argv[0]);
    //     return 1;
    // }

    FILE* arquivoEntrada;
    FILE* arquivoSaida;
    arquivoEntrada = fopen("exemplo1.pgm", "r");
    arquivoSaida = fopen("saida.pgmc", "w");

    Arquivo *novoArquivo;
    novoArquivo = lerArquivo(arquivoEntrada);
    

}




