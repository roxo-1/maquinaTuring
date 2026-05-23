#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ALFABETO 31
#define MAX_ESTADOS 51
#define MAX_TRANSICOES 500
#define MAX_FITA 101

typedef struct {
    int estado_origem;
    char leitura;
    char gravacao;
    char movimento;
    int estado_destino;
} Transicao;

int main() {
    // Abrindo os arquivos de entrada e saída
    FILE *entrada = fopen("entrada.txt", "r");
    FILE *saida = fopen("saida.txt", "w");

    if (entrada == NULL) {
        printf("Erro ao abrir arquivo de entrada!\n");
        return 1;
    }

    char alfabeto[MAX_ALFABETO];
    int num_estados, num_transicoes, num_palavras;
    Transicao tabela[MAX_TRANSICOES];

    // lê o arquivo:
    // Lê o alfabeto
    if (fscanf(entrada, "%s", alfabeto) == EOF) return 0;
    
    // Lê número de estados (estado inicial = 1, aceitação = último) 
    fscanf(entrada, "%d", &num_estados);
    
    // Lê o número de transições
    fscanf(entrada, "%d", &num_transicoes);

    for (int i = 0; i < num_transicoes; i++) {
        // Formato: estado_atual leitura gravar mover proximo_estado
        fscanf(entrada, "%d %c %c %c %d", 
              &tabela[i].estado_origem, 
              &tabela[i].leitura, 
              &tabela[i].gravacao, 
              &tabela[i].movimento, 
              &tabela[i].estado_destino);
    }

    // proceessa palavra
    fscanf(entrada, "%d", &num_palavras);
    int estado_aceitacao = num_estados; 

    for (int p = 1; p <= num_palavras; p++) {
        char palavra[MAX_FITA];
        char fita[MAX_FITA];
        fscanf(entrada, "%s", palavra);

        // Inicializa a fita com o símbolo branco '-' 
        memset(fita, '-', MAX_FITA - 1);
        fita[MAX_FITA - 1] = '\0';
        strncpy(fita, palavra, strlen(palavra));

        int estado_atual = 1; 
        int cabecote = 0;
        bool parou = false;

        // Simulação baseada na função de mapeamento
        while (estado_atual != estado_aceitacao && !parou) {
            bool encontrou_transicao = false;

            for (int i = 0; i < num_transicoes; i++) {
                if (tabela[i].estado_origem == estado_atual && tabela[i].leitura == fita[cabecote]) {
                    fita[cabecote] = tabela[i].gravacao;
                    estado_atual = tabela[i].estado_destino;
                    
                    if (tabela[i].movimento == 'D') cabecote++;
                    else cabecote--;

                    if (cabecote < 0) cabecote = 0;
                    
                    encontrou_transicao = true;
                    break;
                }
            }

            if (!encontrou_transicao) parou = true;
        }

        // saída 
        fprintf(saida, "%d: %s %s\n", p, palavra, (estado_atual == estado_aceitacao ? "OK" : "not OK"));
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}
