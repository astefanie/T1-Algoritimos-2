#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <time.h>
#define TAM 11
using namespace std;

int getch(void) {
  return _getch();
  }


void sobre(){ // Função do menu.
    cout << "Equipe de desenvolvimento: " << endl
         << "Stefanie Saffnauer" << endl
         << "João Victor Atallah" << endl
         << "Diogo Lucas" << endl
         << "Setembro, 2026\n" << endl
         << "Disciplina de Algoritimos II" << endl
         << "Professor: Thiago Felski" << endl
         << "W, A, S, D - movimenta para cima, esquerda, baixo e direita respectivamente" << endl     
         << "Q - gira para esquerda" << endl
         << "E - gira para direita" << endl                
         << "R - reinicia a fase" << endl
         << "ESC - volta ao menu" << endl 
         << "Pressione enter para continuar: ";
}
void EscondeCursor() { //função que esconde o cursor no terminal
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 1;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void FundoAzul() { //função para alterar a cor
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

void CorNormal() { //função para voltar a cor normal
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}



void carregarMapa(int numeroMapa, int m[][TAM], int blocos[][TAM], int &px, int &py){ //função responsavel por carregar os mapas 

    for (int l =0; l<TAM; l++){
        for(int c = 0; c<TAM; c++){
            blocos[l][c] = 0;
        }
    }

  switch (numeroMapa){

    case 1:{
      int temp[TAM][TAM] = { // mapa 1
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,2,4,0,0,1,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,1,0,1},
    {1,0,0,1,0,0,0,1,0,0,1},
    {1,1,0,1,1,1,0,1,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,1},
    {1,1,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,5,1},
    {1,1,1,1,1,1,1,1,1,1,1}
};
  
      for(int l = 0; l < TAM; l++){
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }

      blocos[3][5] = 1; //coordenadas nos blocos presentes na matriz do mapa 1
      blocos[5][7] = 1;
      blocos[7][6] = 1;

      px = 1; //jogador no mapa 1
      py = 1;
      break;
      }

    case 2:{
      int temp[TAM][TAM] = { //mapa 2
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,5,1,1},
    {1,0,1,0,1,0,1,0,0,0,1},
    {1,0,1,0,0,0,1,0,1,0,1},
    {1,0,1,1,6,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,1},
    {1,1,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,0,1},
    {1,2,4,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1}
};

      for(int l = 0; l < TAM; l++){
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }

      blocos[7][5] = 1; //coordenadas nos blocos presentes na matriz do mapa 2
      blocos[5][6] = 1;

      px = 9; //jogador no mapa 2
      py = 1;
      break;
      }

    case 3:{
      int temp[TAM][TAM] = { //mapa 3
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,2,4,0,0,1,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,1,0,1},
    {1,0,0,1,0,0,0,1,0,0,1},
    {1,1,0,1,1,6,0,1,0,1,1},
    {1,0,0,0,0,1,1,1,0,0,1},
    {1,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,1,1,4,0,1},
    {1,1,1,1,0,0,0,7,0,0,1},
    {1,0,0,0,0,0,0,1,0,5,1},
    {1,1,1,1,1,1,1,1,1,1,1}
};

      for(int l = 0; l < TAM; l++){ 
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }

      blocos[2][6] = 1; //coordenadas nos blocos presentes na matriz do mapa 3
      blocos[4][6] = 1;
      blocos[6][4] = 1;
      blocos[8][8] = 1;

      px = 1; // jogador no mapa 3
      py = 1;
      break;
      }
      case 4:{
        numeroMapa = rand() % 3 + 1;
        carregarMapa(numeroMapa, m, blocos, px, py);
      }
    }  
}

bool portaEstaFechada(int celula, int orientacao){ //função responsavel por dizer que as portas estão fechadas
  if (celula == 6){
    if(orientacao == 0 or orientacao == 180){
      return true;
    }else{
      return false;
    }
  }  
  if (celula == 7){
    if(orientacao == 90 or orientacao == 270){
      return true;
    }else{
      return false;
    }
  } 
  return false;
}

bool daPraPassar(int celula, int orientacao){ //confere se os espaços da matriz são atravessaveis e retorna "true" ou "false"
  if(celula == 0 or celula == 4 or celula == 5){ 
    return true;
    }
  else if(celula == 1 or celula == 3){
    return false;
  }
  else if(celula == 6 or celula == 7){
    if (portaEstaFechada(celula, orientacao)){
      return false;
    }else{
      return true;
    }
  }
  return false;
}

void moverJogador(int m[][TAM], int blocos[][TAM], int &px, int &py, int &elementoAbaixo, int orientacao, int &movimentos, char tecla){ //move o jogador dentro da matriz 
  int proxX = px; //variaveis auxiliares
  int proxY = py;

  switch (tecla){ //switch que faz o jogador poder se mover

    case 'w':
    case 'W': {
      proxX = px - 1; 
      break;
    }
    case 's':
    case 'S': {
      proxX = px + 1;
      break;
    }
    case 'a':
    case 'A': {
      proxY = py - 1;
      break;
    }
    case 'd':
    case 'D': {
      proxY = py + 1;
      break;
    }
  }
  if(blocos[proxX][proxY] == 0 && daPraPassar(m[proxX][proxY], orientacao)){ 
    m[px][py] = elementoAbaixo; //devolve o chão antigo
    px = proxX; //atualiza as coordenadas
    py = proxY; //atualiza as coordenadas
    elementoAbaixo = m[px][py]; //guarda o novo chão
    m[px][py] = 2; //coloca o jogador na nova posição
    movimentos++; //soma um movimento 
    }
}
void localizarJogador(int m[][TAM], int &px, int &py){
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
      if(m[l][c] == 2){ //para encontar o jogador
        px = l;
        py = c;
        return;
      }
    }
  }
}

void girarMatriz(int m[][TAM], int blocos[][TAM], int &px, int &py, int &elementoAbaixo, int &orientacao, int &rotacoes, char tecla){
  int aux[TAM][TAM]; //matrizes auxiliares usadas para armazenar temporariamente
  int auxBlocos[TAM][TAM];
  
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
      if(tecla == 'e' or tecla == 'E'){ //verifica se a tecla pressionada é 'E' ou 'e' para ser girada 90 graus para direita
        aux[c][TAM - 1 - l] = m[l][c]; 
        auxBlocos[c][TAM - 1 - l] = blocos[l][c]; //faz a mesma rotação na matriz que representa os blocos 
      }
      else if(tecla == 'q' or tecla == 'Q'){  
        aux[TAM - 1 - c][l] = m[l][c]; //matriz girada 90 graus para a esquerda
        auxBlocos[TAM - 1 - c][l] = blocos[l][c];// faz a mesma rotação na matriz que representa os blocos
      }
    }
  }
  for(int l = 0; l < TAM; l++){ 
    for(int c = 0; c < TAM; c++){
      m[l][c] = aux[l][c]; //loop que atualiza a matriz do jogo após girar ela 
      blocos[l][c] = auxBlocos[l][c]; //atualiza tambem os blocos
    }
  }
  if(tecla == 'e' or tecla == 'E'){
    orientacao = (orientacao + 90) % 360; //atualiza a orientação em graus da matriz 
  }
  else if(tecla == 'q' or tecla == 'Q'){
    orientacao = (orientacao - 90 + 360) % 360; //atualiza a orientação em graus da matriz, o +360 evita que o codigo seja negativo
  }
  rotacoes++; //aumenta a contagem de rotações
  localizarJogador(m, px, py); //apos as rotações procura novamente a posição do jogador
  elementoAbaixo = 4; //define o a alavanca como 4 
}

void esmagamento(int m[][TAM], int blocos[][TAM], int orientacao){
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){

      if(blocos[l][c] == 1){ //verifica se existe um bloco, o valor 1 significa que o bloco pode ser esmagado
        if((m[l][c]==6 || m[l][c]==7) && portaEstaFechada(m[l][c], orientacao)){ //verifica se nessa mesma posição existe alguma porta que pode esmagar o bloco
            blocos[l][c] = 0; //remove o bloco, alterando para 0
        }
      }
    }
  }
}
bool sustentaBloco(int celula, int orientacao){
  if(celula == 1){ //se for igual a 1 sustenta o bloco
    return true;
  }
  else if(celula == 7 || celula == 6){
    return portaEstaFechada(celula, orientacao); //verifica se a porta esta fechada
  }
  return false;
}

void gravidade(int m[][TAM], int blocos[][TAM], int orientacao){

    for (int l= TAM-2; l>= 0; l--){ //percorre as linhas de baixo para cima 
        for (int c = 0; c < TAM; c++){
            if(blocos[l][c] == 1){ //verifica se tem bloco
                int linha = l; //guarda linha do bloco

                while(linha + 1 < TAM && blocos[linha + 1][c] == 0 && sustentaBloco(m[linha + 1][c], orientacao) == false) { //continua movimentando para baixo
                    blocos[linha][c] = 0; //remove o bloco da posição atual
                    blocos[linha + 1][c] = 1; //coloca o bloco uma linha abaixo

                    linha ++;
                }
            }
        }
    }
}

void desenharCenario(int m[][TAM], int blocos[][TAM], int mapaAtual, int orientacao, int movimentos, int rotacoes){

  cout << "Mapa: " << mapaAtual << endl;
  cout << "Orientação: " << orientacao << endl;
  cout << "Movimentos: " << movimentos << endl;
  cout << "Rotações: " << rotacoes << endl;

  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
        
        if(blocos[l][c] == 1){ //verifica se tem bloco
            cout << "O";
        } else {
      switch (m[l][c]) {
        case 0:
          cout << "  ";
          break;
        case 1:
          FundoAzul();
          cout << "  ";
          CorNormal();
          break;
        case 2:
          cout << "@ ";
          break;
        case 3:
          cout << "O ";
          break;
        case 4:
          cout << "A ";
          break;
        case 5:
          cout << "S ";
          break;
        case 6:
          if(portaEstaFechada(6, orientacao) == true){
            cout << "= ";
          }else{
            cout << ": ";
          }
          break;
        case 7:
          if(portaEstaFechada(7, orientacao) == true){
            cout << "| ";
          }else{
            cout << "; ";
          }
          break;
          default:
            cout << "  ";
      }
     }
    }
    cout << endl;
  }
}

bool jogadorNaAlavanca(int elementoAbaixo) {
    if (elementoAbaixo == 4) {
        return true;
    }

    return false;
}

bool venceu(int elementoAbaixo){
    if(elementoAbaixo == 5){
        return true;
    }
    return false;
}

bool jogadorEsmagado(int elementoAbaixo, int orientacao) {

    if (elementoAbaixo == 7 || elementoAbaixo == 6) {

        if(portaEstaFechada(elementoAbaixo, orientacao)) {
            return true;
        }
    }
    return false;
}

void jogar(int m[][TAM], int blocos[][TAM], int numeroMapa, int &px, int &py, int &orientacao, int &movimentos, int &rotacoes, int &elementoAbaixo, bool &jogoSalvo) {
    char tecla;

    while(true) {

        cout << "\033c";

        desenharCenario(m, blocos, numeroMapa, orientacao, movimentos, rotacoes);

        tecla = getch();

        if (tecla == 27) { // tecla ESC
          jogoSalvo = true;
          cout<<"\033c";
          break;
        }
        if (tecla == 'r' || tecla == 'R'){ //reeniciar com a tecla 'r'
            carregarMapa(numeroMapa, m, blocos, px, py);
            orientacao= 0;
            movimentos= 0;
            rotacoes= 0;
            elementoAbaixo= 0;

            continue;
        }

        if (tecla == 'W' || tecla == 'w' || tecla == 'A' || tecla == 'a' || tecla == 'S' || tecla == 's' || tecla == 'D' || tecla == 'd') {

            moverJogador(m, blocos, px, py, elementoAbaixo, orientacao, movimentos, tecla);

            if(venceu(elementoAbaixo)){
                
                desenharCenario(m, blocos, numeroMapa, orientacao, movimentos, rotacoes);
                cout << "\033c";

            cout << "\n====Você venceu!====\n";

            getch();
            break;
           }
        
        } else if( tecla == 'q' || tecla == 'Q' || tecla == 'e' || tecla == 'E') {
            
            if (jogadorNaAlavanca(elementoAbaixo)) {
                
                girarMatriz(m, blocos, px, py, elementoAbaixo, orientacao, rotacoes, tecla);

                esmagamento(m, blocos, orientacao);
                
                gravidade(m, blocos, orientacao);

                if(blocos[px][py] == 1){
                  cout << "\033c";
                  cout << "DERROTA! O jogador for esmagado por um bloco!" << endl;

                  cin.ignore();
                  cin.ignore();
                  cout<<"\033c";

                  break;
                }
               
            }
        }
    }
}




int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(NULL));
    int option;
    int m[TAM][TAM];
    int blocos[TAM][TAM];
    int numeroMapa;
    int px, py;
    bool jogoSalvo = false;

    int orientacao = 0, movimentos = 0, rotacoes = 0;
    int elementoAbaixo = 0;

    char tecla;
    EscondeCursor();
    

    do{
        cout << "--- MENU ---" << endl
             << "1 - Novo Jogo " << endl
             << "2 - Continuar " << endl
             << "3 - Sobre " << endl 
             << "4 - Fim " << endl;
             cout << "Escolha uma opção: " << endl;
             cin >> option;

             cout<<"\033c";

         

        switch (option){

            case 1:
            cout << "Qual mapa gostaria de jogar? 1, 2, 3 ou 4 para aleatorio: " << endl;
            cin >> numeroMapa;

            carregarMapa(numeroMapa, m, blocos, px, py);
            
            orientacao = 0;
            movimentos = 0;
            rotacoes = 0;
            elementoAbaixo = 0;
            
            jogar(m, blocos, numeroMapa, px, py, orientacao, movimentos, rotacoes, elementoAbaixo, jogoSalvo);
            break;

            case 2:
              if(jogoSalvo){
                jogar(m, blocos, numeroMapa, px, py, orientacao, movimentos, rotacoes, elementoAbaixo, jogoSalvo);
              }
            break;

            case 3:
                sobre();
                cin.ignore();
                cin.ignore();
                cout<<"\033c";
                break;

            case 4: 
                cout << "Obrigado(a) por jogar!";
                break;

            default:
                cout << "Opção invalida! ";


    }
    }while (option != 4); 
}