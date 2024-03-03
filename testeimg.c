#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[10];
    int numeroColunas, numeroLinhas, maiorPixel;
    int** matriz;
} Arquivo;

// char lerArquivoCompactado(FILE arquivo*){
//     imagem = fopen("entrada.pgm", "r");

//     if (imagem == null) {
//         print("Erro na leitura do arquivo");
//         return;
//     }

//     char linha[tamanhoLinha];
//     char *leitura;
//     leitura = fgets(linha, 24, imagem); 
    
//     descompactarArquivo(leitura);
// }

// char lerArquivoDescompactado(FILE arquivo*){
//         FILE *imagem;

//         imagem = fopen("entrada.pgmc", "r");

//         if (imagem == null) {
//             print("Erro na leitura do arquivo");
//             return;
//     }

//     char* linha;
//     linha = char* malloc(sizeof(char) * tamanhoLinha);
//     char *leitura;
//     leitura = fgets(linha, tamanhoMatriz, imagem);

//     compactarArquivo(linha);
// }

// char compactarLinha(char *linha, char arqSaida, int *tamanhoLinha){
//     arqSaida = fopen(arqSaida, "w");
//     int conta_repeticao = 0;
//     int marcador = arqSaida[0];
//     int inicio = arqSaida[0];
//     for (int i = 0; i < tamanhoLinha; i++){
//         if(arqSaida[i] == marcador){
//             conta_repeticao += 1;
//             if(conta_repeticao > 3){
//             inicio = (char) "@";
//             arqSaida[inicio + 1] = marcador;
//             arqSaida[inicio + 2] = conta_repeticao;
//             } 
//         }
//         else{
//             conta_repeticao = 0
//             marcador = arqSaida[i];
//             inicio = arqSaida[i];
//         }
//     }
//     return arqSaida;
// }



// char descompactarLinha(char *linha){
    
// }
void printMatriz(int** matriz,int numeroLinha,int numeroColuna){
    for (size_t i = 0; i < numeroLinha; i++){
        for (size_t j = 0; j < numeroColuna; j++){
            printf("%d ",matriz[i][j]);
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
    // else{
    //     novoArquivo->matriz = preencheMatrizCompactada(novoArquivo);
    // }
    
    //Preenche Matriz;
    
    
    // printf("%s\n",&novoArquivo->nome);
    // printf("%d %d\n",novoArquivo->numeroColunas,novoArquivo->numeroLinhas); // teste
    printMatriz(novoArquivo->matriz,novoArquivo->numeroLinhas,novoArquivo->numeroColunas);

    
    // if(novoArquivo->nome == "P2")Compactar(arquivo);
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

// Arquivo transformaArquivo(Arquivo arquivo){
//     int numeroLinhas = arquivo.numeroLinhas;
//     Arquivo *novoArquivo;
//     *novoArquivo = lerArquivo();
    
//     for(int i = 0; i<numeroLinhas;i++){
        
//     }
    
// }





/* int matriz[linhas][colunas];
int conta_repeticao = 0;
int marcador = matriz[0][0];
for (i = 0; i < linhas; i++){
conta_repeticao = 0;
int inicio = matriz[i][j]; 
int num_repetido = matriz[i+1] []]; 
int quantidade = matriz[i+2][j]; 

for (j = 0; j < colunas; i++){
    if (matriz[i][j] == marcador){
        conta_repeticao += 1; 

        if (conta_repeticao > 3){ 
            inicio = (char) "@"; 
            num_repetido = marcador; 
            quantidade = conta_repeticao;
        }

    else{
        conta_repeticao = 0;
        marcador = matriz[i][j];
} */

// if (valor[i] == "@")

