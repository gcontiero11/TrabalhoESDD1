#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char tipo[3];
    int colunas, linhas, maiorPixel;
    char** matriz;
} Imagem;

Imagem lerArquivo(FILE *arquivo){
    Imagem imagem;

    fscanf(arquivo, "%s %d %d %d", imagem.tipo, &imagem.colunas, &imagem.linhas, &imagem.maiorPixel);

    printf("%s \n", imagem.tipo);
    printf("%d %d \n", imagem.colunas, imagem.linhas);
    printf("%d", imagem.maiorPixel);



    return imagem;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s arquivo_entrada arquivo_saida\n", argv[0]);
        return 1;
    }

    FILE *arquivoEntrada = fopen("exemplo1.pgm", "r");

    if (arquivoEntrada == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    lerArquivo(arquivoEntrada);
    
    
    
    fclose(arquivoEntrada);
    return 0;
}