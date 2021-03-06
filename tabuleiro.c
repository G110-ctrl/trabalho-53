#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cores.h"
#include "usuario.h"
#include "verificacao.h"

void pecas_disponiveis(char **pecas, char *disponivel, int quant, int num_jog) {
  
  int linha = 0;
  int coluna = 0;
  int static sorteio = 0;
  int aux_quant;
  int aux_falta;
  
  aux_quant = 12 - quant;
  aux_falta = quant;

  if(sorteio == 0) {
    srand(time(NULL));
  }
  sorteio = !sorteio;

  coluna = rand() % 36;

  for(int i = 0; i < aux_quant; i += 2) {       
    while(coluna % 2 != 0) {
      coluna = rand() % 36;      
    }
  
    linha = rand() % 6;

    if(pecas[linha][coluna] != ' ') {
      disponivel[aux_falta] = pecas[linha][coluna];
      disponivel[aux_falta + 1] = pecas[linha][coluna + 1];
      aux_falta += 2;
    }
    else {
      i += -2;    // Decrementa i para procura outra posição
    }
    coluna = rand() % 36;   
  }
  return;
}

void imprimir_disponivel(char *disponivel, int quant) {

  //impressao de pecas disponiveis para jogada
  for(int i = 0; i < quant; i += 2) {
    switch(disponivel[i + 1]) {
      case '1': 
        verde();
        printf("%c%c ", disponivel[i], disponivel[i + 1]);
        padrao();
        break;
      case '2': 
        vermelho();
        printf("%c%c ", disponivel[i], disponivel[i + 1]);
        padrao();
        break;
      case '3': 
        amarelo();
        printf("%c%c ", disponivel[i], disponivel[i + 1]);
        padrao();
        break;
      case '4': 
        azul();
        printf("%c%c ", disponivel[i], disponivel[i + 1]);
        padrao();
        break; 
      case '5': 
        roxo();
        printf("%c%c ", disponivel[i], disponivel[i + 1]);
        padrao();
        break; 
      case '6': 
        marinho();
        printf("%c%c ", disponivel[i], disponivel[i + 1]);
        padrao();
        break;      
    } 
  }
  printf("\n");
  return;
}

void imprimir_tabuleiro(char **tabuleiro, int linha, int coluna, int linha_superior, int coluna_esquerda) {

//laços para impressao do tabuleiro
  for(int i = 0; i < coluna; i += 2) {
    if(linha_superior < 0) {
      printf("   %d", linha_superior);
    }
    else {
      printf("    %d", linha_superior);
    } 
    linha_superior++;
  }
  printf("\n");

  for(int i = 0; i < linha; i++) {
    if(coluna_esquerda < 0) {
      printf("%d ", coluna_esquerda);
    }
    else {
      printf(" %d ", coluna_esquerda);
    }    
    for(int j = 0; j < coluna; j += 2) {
      switch(tabuleiro[i][j + 1]) {
        case '1': 
          printf("|");
          verde();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]);
          padrao();
          printf("| ");
          break; 
        case '2': 
          printf("|");
          vermelho();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '3':
          printf("|");
          amarelo();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '4':
          printf("|");
          azul();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '5': 
          printf("|");
          roxo();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '6':
          printf("|");
          marinho();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        default: 
          printf("|%c%c| ", tabuleiro[i][j], tabuleiro[i][j + 1]); 
      }      
    }
    printf("\n");
    coluna_esquerda++;
  } 
  return;
}

int opcoes(void) {

  int flag;
  int seleciona;
  char *entrada;

  entrada = (char *) malloc(sizeof(char) * 100);
  if(entrada == NULL) {
    vermelho();
    printf("Nao foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  
  //funcoes para o comando do jogador na sua respectiva vez
  verde();
  printf("Opcoes:\n");
  padrao();
  printf("1 - Jogar |");
  printf(" 2 - Trocar |");
  printf(" 3 - Passar\n");

  verde();
  printf("Qual a opcao desejada: ");
  padrao();
 
 //caso para entradas de erro
  do {
    flag = 0;
    scanf("%s", entrada);
    if(is_alpha(entrada) == 1) {
      vermelho();
      printf("Voce nao digitou um numero !!\n");
      printf("Digite o valor corretamente: ");
      padrao();      
    }
    else {
      seleciona = atoi(entrada);      
      if(seleciona < 1 || seleciona > 3) {
        vermelho();
        printf("Valor invalido, digite novamente: ");
        padrao();
        flag = 1;
      }      
    }
  } while((is_alpha(entrada) == 1) || flag == 1);
  
  free(entrada);  

  return seleciona;
}

void troca_peca(char **pecas, char *disponivel, int quant_disponivel) {

  char jogada[10];
  int existe = 0;
  int i, j;
  
  //entradas para trocar as pecas
  verde();
  printf("Qual peca deseja trocar: ");
  padrao();
  do {
    setbuf(stdin, NULL);  
    fgets(jogada, 10, stdin);

    for(i = 0; i < quant_disponivel; i += 2) {
      if((jogada[0] == disponivel[i]) && (jogada[1] == disponivel[i + 1])) {
        existe = 1;
        break;
      }      
    }
    //entrada de erro para a troca de peca
    if(!existe) {
      vermelho();
      printf("A peca que deseja trocar nao existe. Escolha novamente: ");
      padrao();
    }
  } while(!existe);

  // Sorteio de uma nova peça

  int linha;
  int coluna;

  srand(time(NULL));
  coluna = rand() % 36;

  for(j = 0; j < 2; j += 2) {    
    while(coluna % 2 != 0) {
      coluna = rand() % 36;      
    }

    linha = rand() % 6;

    if(pecas[linha][coluna] != ' ') {
      disponivel[i] = pecas[linha][coluna];
      disponivel[i + 1] = pecas[linha][coluna + 1];
    }
    else {
      i += -2;    // Decrementa i para procura outra posição
    }
    coluna = rand() % 36;
  }
  return;
}

void cont_pontos(char **tabuleiro, int pos1, int pos2, int linha, int coluna, int *pontos, int quant_jog) {
  
  //nesta funcao, é feita a contagem dos pontos 
  int soma = 0;
  int qtd_pecas_seguidas = 0;

  // Posições a direita da peça 
  if(pos2 != (coluna - 2) && tabuleiro[pos1][pos2 + 2] != ' ') {
    for(int i = pos2; i < coluna; i += 2) {
      if(tabuleiro[pos1][i] != ' ') {
        soma++;
        qtd_pecas_seguidas++;
      }
    }
  }
  // Posições a esquerda da peça
  if(pos2 != 0 && tabuleiro[pos1][pos2 - 2] != ' ') {
    for(int i = pos2; i >= 0; i += -2) {
      if(tabuleiro[pos1][i] != ' ') {
        soma++;
        qtd_pecas_seguidas++;
      }
    }
  }
  // Posições acima da peça
  if(pos1 != 0 && tabuleiro[pos1 - 1][pos2] != ' ') {
    for(int i = pos1; i >= 0; i--) {
      if(tabuleiro[i][pos2] != ' ') {
        soma++;
        qtd_pecas_seguidas++;
      }
    }
  }
  // Posiçoes abaixo da peça
  if(pos1 != (linha - 1) && tabuleiro[pos1 + 1][pos2] != ' ') {
    for(int i = pos1; i < linha; i++) {
      if(tabuleiro[i][pos2] != ' ') {
        soma++;
        qtd_pecas_seguidas++;
      }
    }
  }
  if(qtd_pecas_seguidas == 6){
    pontos[quant_jog] += 6;
    qtd_pecas_seguidas = 0;
  }
  if(soma == 0) {
    pontos[quant_jog]++;  
  }
  else {
    pontos[quant_jog] += soma;
  }
  return;
}

void quadro_pecas(char **pecas, char **tabuleiro, char **jogadores, int num_jog, int mode) {

  int linha = 1;
  int linha_superior = 0;
  int coluna = 2;
  int coluna_esquerda = 0;
  int i, j;         // Contadores 
  char **disponivel;
  int *num_sorteio;
  int *pontos;

  disponivel = (char **) malloc(sizeof(char) * num_jog);
  if(disponivel == NULL) {
    vermelho();
    printf("Não foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  for(i = 0; i < num_jog; i++) {
    disponivel[i] = (char *) malloc(sizeof(char) * 12);
    if(disponivel[i] == NULL) {
      vermelho();
      printf("Não foi possivel alocar memoria\n");
      padrao();
      exit(1);
    }
  }
  
  num_sorteio = (int *) malloc(sizeof(int) * num_jog);
  if(num_sorteio == NULL) {
    vermelho();
    printf("Não foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  // Inicializa o vetor num_sorteio
  for(i = 0; i < num_jog; i++) {
    num_sorteio[i] = 0; 
  }

  pontos = (int *) malloc(sizeof(char) * num_jog);
  if(pontos == NULL) {
    vermelho();
    printf("Não foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  for(i = 0; i < num_jog; i++) {
    pontos[i] = 0; // Inicializa com 6 peças 
  }

  // Aloca a primeiro linha e as duas colunas iniciais 
  tabuleiro = NULL;
  tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);
  if(tabuleiro == NULL) {
    vermelho();
    printf("Nao foi possivel adicinar linhas no tabuleiro\n");
    padrao();
    exit(1);
  }
  tabuleiro[0] = NULL;
  tabuleiro[0] = (char *) realloc(tabuleiro[0], sizeof(char) * coluna);   // Duas colunas (1 peça)
  if(tabuleiro[0] == NULL) {
    vermelho();
    printf("Nao foi possivel adicinar colunas no tabuleiro\n");
    padrao();
    exit(1);
  }
  tabuleiro[0][0] = ' ';
  tabuleiro[0][1] = ' ';

  char jogada[10];      // Armazena a peça digitada pelo usuario
  int pos1, pos2;       // Posição do tabuleiro impresso
  int existe = 0;       // Auxilia na verificação de existencia de peças 
  int ref_linha = 0, ref_coluna = 0;  // Relação entre o valor da posição digitada com as coordenadas das peças no vetor
  int quant_disponivel = 12; // Peças disponiveis para os jogadores em cada rodada
  int quant_jog = 0;      // Quantidade de jogadores
  int quant_pecas = 108;  // Quantidade total de peças
  int lim_linha = 1;  // Quantidade de linhas que o usuario pode escolher 
  int lim_coluna = 1; // Quantidade de colunas que o usuario pode escolher 
  int valida = 1; // Verifica se a jogada é valido
  int ult_linha = 0;
  int ult_coluna = 0;
  int sair;
  int seleciona = 0;
  int flag = 0;
  int linha_atual = 1;
  int cheat = 0;

  for(i = 0; i < num_jog; i++) {
    pecas_disponiveis(pecas, disponivel[i], num_sorteio[i], num_jog);
    num_sorteio[i] = 12;
  }
  do {    
    if(quant_jog == num_jog) {
      quant_jog = 0;
    }
    if(num_sorteio[quant_jog] != 0) {
      imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior, coluna_esquerda);
      for(i = 0; i < num_jog; i++) {
        verde();
        printf("Jogador ");
        amarelo();
        printf("%s ", jogadores[i]);
        azul();
        printf("(score: %d)\n", pontos[i]);
        padrao();
      }
    }
    sair = 0;
    do {
      do {
        if(!valida) {
          imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior, coluna_esquerda);
        }
        printf("------------------------\n");
        verde();
        printf("Jogada de ");
        amarelo();
        printf("%s\n", jogadores[quant_jog]);
        negrito();
        printf("Pecas disponiveis: ");
        padrao();
        imprimir_disponivel(disponivel[quant_jog], quant_disponivel);
        seleciona = opcoes();   // Opções selecionadas pelo jogador da rodada atual

        if(seleciona == 2) {   // Troca das peças
          do {
            troca_peca(pecas, disponivel[quant_jog], quant_disponivel);
            imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior, coluna_esquerda);
            for(i = 0; i < num_jog; i++) {
              verde();
              printf("Jogador ");
              amarelo();
              printf("%s ", jogadores[i]);
              azul();
              printf("(score: %d)\n", pontos[i]);
              padrao();
            }
            printf("------------------------\n");
            verde();
            printf("Jogada de ");
            amarelo();
            printf("%s\n", jogadores[quant_jog]);   
            negrito();
            printf("Pecas disponiveis: ");
            padrao();
            imprimir_disponivel(disponivel[quant_jog], quant_disponivel);
            seleciona = opcoes();   
          } while(seleciona == 2);     
        }

        if(seleciona == 3) {   // Passa a vez para o proximo adversario
          sair = 1;
          break;
        }

        negrito();
        printf("Escolha a peca desejada: ");
        padrao();
        existe = 0;
      
        do { // Verifica se a peça selecionada pelo usuario existe          
          setbuf(stdin, NULL);
          fgets(jogada, 10, stdin);  
          
          for(i = 0; i < quant_disponivel; i += 2) {
            if((jogada[0] == disponivel[quant_jog][i]) && (jogada[1] == disponivel[quant_jog][i + 1])) {
              existe++;
              break;
            }      
          }
          if(mode == 1) {
            for(i = 0; i < 6 && !cheat; i++) { 
              for(j = 0; j < 36; j += 2) {
                if(pecas[i][j] == jogada[0] && pecas[i][j + 1] == jogada[1]) {
                  existe++;
                  break;
                }
              }
            }
          }                        
          if(!existe) {
            vermelho();
            printf("Peca invalida, escolha novamente: "); 
            padrao();
          }
        } while(!existe);
         
        do {
          negrito();
          printf("Linha: ");
          padrao();
          
          char *pos_aux;
          pos_aux = (char *) malloc(sizeof(char) * 100);
          if(pos_aux == NULL) {
            vermelho();
            printf("Não foi possivel alocar memoria\n");
            padrao();
            exit(1);
          }                  
          do {
            existe = 0;
            setbuf(stdin, NULL);
            fgets(pos_aux, 100, stdin);
            if(is_alpha(pos_aux) == 1) {
              vermelho();
              printf("Digite um numero: ");
              padrao();
              existe = 1;
            }
            else {
              pos1 = atoi(pos_aux);
              if(pos1 < coluna_esquerda || pos1 >= lim_linha) {
                vermelho();
                printf("Linha invalida, digite novamente: ");
                padrao();
                existe = 1;
              }
            }          
          } while(existe);

          negrito();
          printf("Coluna: ");
          padrao();
          do {
            existe = 0;
            scanf("%s", pos_aux);
            if(is_alpha(pos_aux) == 1) {
              vermelho();
              printf("Digite um numero: ");
              padrao();
              existe = 1;
            }
            else {
              pos2 = atoi(pos_aux);
              if(pos2 < linha_superior || pos2 >= lim_coluna) {
                vermelho();
                printf("Coluna invalida, digite novamente: ");
                padrao();
                existe = 1;
              }
            }
          } while(existe);
          
          free(pos_aux);
          // Relaciona as posições impressas com as posições da matrzi tabuleiro 

          i = ref_linha + pos1;
          j = ref_coluna + pos2;
          j = 2 * j; 

          if(tabuleiro[i][j] != ' ') {
            vermelho();
            printf("Posicao ja preenchida, insira novamente\n");
            padrao();
          }                             
        } while(tabuleiro[i][j] != ' '); 

        valida = jog_valida(tabuleiro, jogada, i, j, linha, coluna, linha_atual);   
        if(valida && linha_atual) {
          ult_linha = i;
          ult_coluna = j;        
        }        
        if(!valida) {
          vermelho();
          printf("Jogada invalida\n");
          padrao();
        }               
        linha_atual = 0; 
      } while(!valida);  // enquanto a jogada não for valida

      if(sair == 1) { // troca o jogador
        valida = 1;
        linha_atual = 1;                   
        break;
      }

      tabuleiro[i][j] = jogada[0];
      tabuleiro[i][j + 1] = jogada[1];
      
      // Apaga do vetor disponivel a peça jogada
      int k = 0, elimina = 0;      
      for(i = 0; i < num_sorteio[quant_jog]; i += 2) {
        if(disponivel[quant_jog][i] != jogada[0] || disponivel[quant_jog][i + 1] != jogada[1] || elimina) {
          disponivel[quant_jog][k] = disponivel[quant_jog][i];
          disponivel[quant_jog][k + 1] = disponivel[quant_jog][i + 1];
          k += 2;      
        }
        else {
          elimina = 1;
        }        
      }
      if(elimina == 1) {        
        num_sorteio[quant_jog] += -2;        
        disponivel[quant_jog][num_sorteio[quant_jog]] = ' ';
        disponivel[quant_jog][num_sorteio[quant_jog] + 1]  = ' ';
        elimina = 0;
      }

      // Apaga do da matriz pecas(onde são listadas todas as peças do jogo)a peça que foi inserida do tabuleiro
      flag = 0;  
      for(i = 0; i < 6 && !flag; i++) { 
        for(j = 0; j < 36 && !flag; j += 2) {
          if(pecas[i][j] == jogada[0] && pecas[i][j + 1] == jogada[1]) {
            pecas[i][j] = ' ';
            pecas[i][j + 1] = ' ';
            quant_pecas--;
            if(quant_pecas == 0) {
              break;
            }
            flag = 1;
          }
        }    
      }
      
      // Verificação na linha superior
      flag = 0;
      for(i = 0; i < coluna; i++) { 
        if(tabuleiro[0][i] != ' ') { // Se a linha mais superior não estiver vazia
          ult_linha++;
          coluna_esquerda += -1;
          ref_linha++;
          flag = 1;
          break;
        }
      }
      
      if(flag) {
        linha += 1;     // Aumenta a quantidade de linhas 
        tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);
        if(tabuleiro == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar linhas no tabuleiro\n");
          padrao();
          exit(1);
        }
        tabuleiro[linha - 1] = NULL;
        tabuleiro[linha - 1] = (char *) realloc(tabuleiro[linha - 1], sizeof(char ) * coluna);
        if(tabuleiro[linha - 1] == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar colunas no tabuleiro\n");
          padrao();
          exit(1);
        }
        
        // Inicializa as posições alocadas
        for(i = 0; i < coluna; i++) {
          tabuleiro[linha - 1][i] = ' ';
        }
        
        // Coloca as peças uma posição abaixo na matriz tabuleiro 
        int copia = linha - 2;
        for(i = 0; i < (linha - 1); i++) {
          for(j = 0; j < coluna; j += 2) {
            if(tabuleiro[copia][j] != ' ') { 
              tabuleiro[copia + 1][j] = tabuleiro[copia][j];
              tabuleiro[copia + 1][j + 1] = tabuleiro[copia][j + 1];
              tabuleiro[copia][j] = ' ';
              tabuleiro[copia][j + 1] = ' ';
            }
          }
          copia += -1;
        }
      }

      // Adiciona linha mais inferior da matriz tabuleiro
      flag = 0;
      for(i = 0; i < coluna; i++) {
        if(tabuleiro[linha - 1][i] != ' ') {  // verifica se a ultima linha da matriz tem peças 
          linha += 1;
          flag = 1;
          break;
        }
      }

      lim_linha = linha + coluna_esquerda; // limita os valores das linhas que podem ser inseridos pelo usuario

      if(flag) {
        tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);   // adicinar uma linha
        if(tabuleiro == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar linhas no tabuleiro\n");
          padrao();
          exit(1);
        }
        tabuleiro[linha - 1] = (char *) realloc(tabuleiro[linha - 1], sizeof(char ) * coluna);  // Aloca as colunas na nova linha alocada 
        if(tabuleiro[linha - 1] == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar colunas no tabuleiro\n");
          padrao();
          exit(1);
        }
        // Inicializa a nova linha alocada
        for(i = 0; i < coluna; i++) {
          tabuleiro[linha - 1][i] = ' ';  
        }
      }

      // Verifica a coluna mais a esquerda 
      flag = 0;
      for(i = 0; i < linha; i++) {
        if(tabuleiro[i][0] != ' ') {    // Se a coluna esquerda não estiver vazia
          ult_coluna += 2;
          linha_superior += - 1;
          ref_coluna += 1;
          flag = 1;
          break;
        }
      }
      // Adiciona colunas e reorganiza as peças na matriz
      if(flag) {
        coluna += 2;      // Adiciona 2 colunas para inserir uma peça a esquerda
        for(i = 0; i < linha; i++) {
          tabuleiro[i] = (char *) realloc(tabuleiro[i], sizeof(char ) * coluna);
          if(tabuleiro[i] == NULL) {
            vermelho();
            printf("Nao foi possivel adicinar colunas no tabuleiro\n");
            padrao();
            exit(1);
          }
          // Inicializa as colunas alocadas
          tabuleiro[i][coluna - 2] = ' '; 
          tabuleiro[i][coluna - 1] = ' ';      
        }
        // Movimenta todas as peças para a direita do tabuleiro
        int copia = linha - 1;
        for(i = 0; i < (linha - 1); i++) {
          for(j = (coluna - 4); j >= 0; j += -2) {
            if(tabuleiro[copia][j] != ' ') {
              tabuleiro[copia][j + 2] = tabuleiro[copia][j];
              tabuleiro[copia][j + 3] = tabuleiro[copia][j + 1];
              tabuleiro[copia][j] = ' ';
              tabuleiro[copia][j + 1] = ' ';
            }
          }
          copia += -1;
        }
      }

      // Adiciona coluna a direita do tabuleiro
      flag = 0;
      for(i = 0; i < linha; i++) {
        if(tabuleiro[i][coluna - 1] != ' ') {
          coluna += 2; // Adicina mais duas colunas (Armazena mais uma peça) 
          lim_coluna++;
          flag = 1;
          break;
        }
      }
      
      if(flag) {
        for(i = 0; i < linha; i++) {
          tabuleiro[i] = (char *) realloc(tabuleiro[i], sizeof(char) * coluna);
          if(tabuleiro[i] == NULL) {
            vermelho();
            printf("Nao foi possivel adicionar novas colunas no tabuleiro\n");
            padrao();
            exit(1);
          }
          // Inicializa as novas colunas alocadas 
          tabuleiro[i][coluna - 2] = ' ';
          tabuleiro[i][coluna - 1] = ' ';      
        }
      }

      // Imprimir tabuleiro
      imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior,  coluna_esquerda);
      for(i = 0; i < num_jog; i++) {
        verde();
        printf("Jogador ");
        amarelo();
        printf("%s ", jogadores[i]);
        azul();
        printf("(score: %d)\n", pontos[i]);
        padrao();
      }
      
      //caso para fim de jogo
      if(quant_disponivel == 0) {
        vermelho();
        printf("Nao existem mais pecas disponiveis !!\n");
        padrao();
      }
    } while(quant_disponivel > 0);

    if(quant_pecas == 0) {
      int maior = pontos[0];
      int ganhador = 0;
      for(i = 1; i < num_jog; i++) {
        if(pontos[i] > maior) {
          maior = pontos[i];
          ganhador = i;
        }
      }
      printf("%s é o vencedor :)\n", jogadores[i]);
      break;
    }

    if(num_sorteio[quant_jog] <= 10) {
      cont_pontos(tabuleiro, ult_linha, ult_coluna, linha, coluna, pontos, quant_jog);
    }

    pecas_disponiveis(pecas, disponivel[quant_jog], num_sorteio[quant_jog], num_jog);
    num_sorteio[quant_jog] = 12;

    quant_jog++; // proximo jogador
    linha_atual = 1;
    
  } while(quant_pecas > 0);

  for(i = 0; i < num_jog; i++) {
    free(disponivel[i]);    
  }
  free(disponivel);
  free(pontos);
  free(num_sorteio);

  return;
}