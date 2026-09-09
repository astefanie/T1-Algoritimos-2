#include <iostream>
#include <conio.h> 
#include <windows.h>
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
void EscondeCursor() {
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 1;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void FundoAzul() {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

void CorNormal() {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}



void carregarMapa(int &numeroMapa, int m[][TAM], int &px, int &py){

  cout << "Qual mapa gostaria de jogar? 1, 2 ou 3: " << endl;
  cin >> numeroMapa;

  switch (numeroMapa){

    case 1:{
      int temp[TAM][TAM] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //mapa 1
                            {1, 2, 4, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
                            {1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 3, 0, 5, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  
      for(int l = 0; l < TAM; l++){
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }
      px = 1; //jogador no mapa 1
      py = 1;
      break;
      }

    case 2:{
      int temp[TAM][TAM] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //mapa 2 
                            {1, 2, 4, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 1, 1, 1, 1, 6, 1, 1, 1, 1, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

      for(int l = 0; l < TAM; l++){
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }
      px = 1; //jogador no mapa 2
      py = 1;
      break;
      }

    case 3:{
      int temp[TAM][TAM] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //mapa 3
                            {1, 2, 4, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1, 4, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1, 0, 5, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

      for(int l = 0; l < TAM; l++){ 
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }
      px = 1; // jogador no mapa 3
      py = 1;
      break;
      }
    }  
}

bool portaEstaFechada(int celula, int orientacao){
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

void moverJogador(int m[][TAM], int &px, int &py, int &elementoAbaixo, int orientacao, int &movimentos, char tecla){
  int proxX = px;
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
  if(daPraPassar(m[proxX][proxY], orientacao)){
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

void girarMatriz(int m[][TAM], int &px, int &py, int &elementoAbaixo, int &orientacao, int &rotacoes, char tecla){
  int aux[TAM][TAM];
  
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
      if(tecla == 'e' or tecla == 'E'){
        aux[c][TAM - 1 - l] = m[l][c]; //logica matematica utilizada para girar a matriz 
      }
      else if(tecla == 'q' or tecla == 'Q'){
        aux[TAM - 1 - c][l] = m[l][c];
      }
    }
  }
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
      m[l][c] = aux[l][c]; //loop que atualiza a matriz do jogo após girar ela 
    }
  }
  if(tecla == 'e' or tecla == 'E'){
    orientacao = (orientacao + 90) % 360; //atualiza a orientação em graus da matriz 
  }
  else if(tecla == 'q' or tecla == 'Q'){
    orientacao = (orientacao - 90 + 360) % 360; //atualiza a orientação em graus da matriz 
  }
  rotacoes++; //aumenta a contagem de rotações
  localizarJogador(m, px, py);
  elementoAbaixo = 4;
}

void esmagamento(int m[][TAM], int &orientacao, int &px, int &py, bool &perdeu){
  for(int l = 0; l < TAM - 1; l++){
    for(int c = 0; c < TAM - 1; c++){

      if(m[l][c] == 6 or m[l][c] == 7){
        portaEstaFechada(m[l][c], orientacao);

          if(m[l][c] == m[px][py]){
            perdeu = true;
          }
          else{
            m[l][c] = 0;
          }
      }
    }
  }
}
bool sustentaBloco(int celula, int orientacao){
  if(celula == 1 or celula == 3){
    return true;
  }
  else if(celula == 7 or celula == 6){
    return(portaEstaFechada(celula, orientacao));
  }
  return false;
}



void desenharCenario(int m[][TAM], int mapaAtual, int orientacao, int movimentos, int rotacoes){

  cout << "Mapa: " << mapaAtual << endl;
  cout << "Orientação: " << orientacao << endl;
  cout << "Movimentos: " << movimentos << endl;
  cout << "Rotações: " << rotacoes << endl;

  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
      switch (m[l][c]) {
        case 0:
          cout << " ";
          break;
        case 1:
          FundoAzul();
          cout << " ";
          CorNormal();
          break;
        case 2:
          cout << "@";
          break;
        case 3:
          cout << "O";
          break;
        case 4:
          cout << "A";
          break;
        case 5:
          cout << "S";
          break;
        case 6:
          if(portaEstaFechada(6, orientacao) == true){
            cout << "=";
          }else{
            cout << ":";
          }
          break;
        case 7:
          if(portaEstaFechada(7, orientacao) == true){
            cout << "|";
          }else{
            cout << ";";
          }
          break;
          default:
            cout << " ";
      }
    }
  }
}




int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int option;

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
            break;

            case 2:
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