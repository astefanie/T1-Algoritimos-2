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



void carregarMapa(int numeroMapa, int m[][TAM], int blocos[][TAM], int &px, int &py){

    for (int l =0; l<TAM; l++){
        for(int c = 0; c<TAM; c++){
            blocos[l][c] = 0;
        }
    }

  switch (numeroMapa){

    case 1:{
      int temp[TAM][TAM] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,4,0,0,1,0,0,0,0,1},
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

      blocos[3][5] = 1;
      blocos[5][7] = 1;
      blocos[7][6] = 1;

      px = 1; //jogador no mapa 1
      py = 1;
      break;
      }

    case 2:{
      int temp[TAM][TAM] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,5,1,1},
    {1,0,1,0,1,0,1,0,0,0,1},
    {1,0,1,0,0,0,1,0,1,0,1},
    {1,0,1,1,6,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,1},
    {1,1,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,0,1},
    {1,0,4,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1}
};

      for(int l = 0; l < TAM; l++){
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }

      blocos[9][5] = 1;
      blocos[5][6] = 1;

      px = 9; //jogador no mapa 2
      py = 1;
      break;
      }

    case 3:{
      int temp[TAM][TAM] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,4,0,0,1,0,0,0,0,1},
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

      blocos[3][6] = 1;
      blocos[4][6] = 1;
      blocos[9][4] = 1;
      blocos[9][8] = 1;

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
  else if(celula == 1){
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

void moverJogador(int m[][TAM], int blocos[][TAM], int &px, int &py, int orientacao, int &movimentos, char tecla){
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
  if(blocos[proxX][proxY] == 0 && daPraPassar(m[proxX][proxY], orientacao)){
    px = proxX; //atualiza as coordenadas
    py = proxY; //atualiza as coordenadas
    movimentos++; //soma um movimento 
    }
}

void girarMatriz(int m[][TAM], int blocos[][TAM], int &px, int &py, int &orientacao, int &rotacoes, char tecla){
  int novoPx;
  int novoPy;
  int aux[TAM][TAM];
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
    novoPx = py; //atualiza a orientação em graus da matriz 
    novoPy = TAM - 1 - px;
    orientacao = (orientacao + 90) % 360;
  } 
  else if(tecla == 'q' or tecla == 'Q'){
    novoPx = TAM - 1 - py; //atualiza a orientação em graus da matriz
    novoPy = px;
    orientacao = (orientacao - 90 + 360) % 360;
  }
    px = novoPx;
    py = novoPy;
    rotacoes++; //aumenta a contagem de rotações
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

void gravidade(int m[][TAM], int blocos[][TAM], int orientacao, int px, int py){

    for (int l= TAM-2; l>= 0; l--){ //percorre as linhas de baixo para cima 
        for (int c = 0; c < TAM; c++){
            if(blocos[l][c] == 1){ //verifica se tem bloco
                int linha = l; //guarda linha do bloco

                while(linha + 1 < TAM && blocos[linha + 1][c] == 0 && !(linha + 1 == px && c == py) && sustentaBloco(m[linha + 1][c], orientacao) == false) {
                    blocos[linha][c] = 0;
                    blocos[linha + 1][c] = 1;

                    linha ++;
                }
            }
        }
    }
}

char jogadorAlavanca(int m[][TAM], int px, int py){
    
    if(m[px][py] == 4){
        return 'T';
    }
    return '@';
}

void desenharCenario(int m[][TAM], int blocos[][TAM], int mapaAtual, int orientacao, int movimentos, int rotacoes, int px, int py){

  cout << "Mapa: " << mapaAtual << endl;
  cout << "Orientação: " << orientacao << endl;
  cout << "Movimentos: " << movimentos << endl;
  cout << "Rotações: " << rotacoes << endl;

  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
        
        if(l == px && c == py){
            cout << jogadorAlavanca(m, px, py) << " ";
        } else if(blocos[l][c] == 1){
            cout << "O ";
        } else{
      switch (m[l][c]) {
        case 0:
          cout << "  ";
          break;
        case 1:
          FundoAzul();
          cout << "  ";
          CorNormal();
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

bool jogadorNaAlavanca(int m[][TAM], int px, int py) {
    if (m[px][py] == 4) {
        return true;
    }

    return false;
}

bool venceu(int m[][TAM], int px, int py){
    if(m[px][py] == 5){
        return true;
    }
    return false;
}

bool jogadorEsmagado(int m[][TAM], int px, int py, int orientacao) {

    if ((m[px][py] == 7 || m[px][py] == 6) && portaEstaFechada(m[px][py], orientacao)){
            return true;
    }

    return false;
}

void jogar(int m[][TAM], int blocos[][TAM], int numeroMapa, int &px, int &py, int &orientacao, int &movimentos, int &rotacoes, bool &jogoSalvo) {
    char tecla;

    while(true) {

        cout << "\033c";

        desenharCenario(m, blocos, numeroMapa, orientacao, movimentos, rotacoes, px, py);

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

            continue;
        }

        if (tecla == 'W' || tecla == 'w' || tecla == 'A' || tecla == 'a' || tecla == 'S' || tecla == 's' || tecla == 'D' || tecla == 'd') {

            moverJogador(m, blocos, px, py, orientacao, movimentos, tecla);

            if(venceu(m, px,py)){
                jogoSalvo = false;

                cout << "\033c";
                
                desenharCenario(m, blocos, numeroMapa, orientacao, movimentos, rotacoes, px, py);

            cout << "\n====Você venceu!====\n";

            getch();
            break;
           }
        
        } else if( tecla == 'q' || tecla == 'Q' || tecla == 'e' || tecla == 'E') {
            
            if (jogadorNaAlavanca(m, px, py)) {
                
                girarMatriz(m, blocos, px, py, orientacao, rotacoes, tecla);

                if(jogadorEsmagado(m, px, py, orientacao)){

                    cout << "\033c";
                    cout << "==== Você foi esmagado pela porta! ====\n";
            
                    getch();

                    carregarMapa(numeroMapa, m, blocos, px, py);
                    orientacao = 0;
                    movimentos = 0;
                    rotacoes = 0;
                    
                    continue;
                }

                esmagamento(m, blocos, orientacao);
                
                gravidade(m, blocos, orientacao, px, py);
            }
        }
    }
}

int escolherMapa(){
    int opcao;
    int mapa;

    cout << "1 - Escolher mapa\n";
    cout << "2 - Mapa aleatório\n"; 
    cout << "Escolha uma opção: ";
    cin >> opcao;

    if(opcao ==1){
        cout << "Escolher o mapa 1, 2 ou 3: ";
        cin >> mapa;

        while(mapa <1 || mapa >3){
            cout << "Mapa inválido. Escolha 1, 2 ou 3: ";
            cin >> mapa;
        }
        return mapa;
    }else if(opcao == 2){
        mapa = rand() % 3 + 1;

        return mapa;
    }

    return 1;
}

void menu(bool jogoSalvo){
    cout << "--- MENU ---" << endl
         << "1 - Novo Jogo " << endl;

    if(jogoSalvo){
         cout << "2 - Continuar " << endl;
    }
         
    cout << "3 - Sobre " << endl 
         << "4 - Fim " << endl
         << "Escolha uma opção: ";
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

    EscondeCursor();
    

    do{
        menu(jogoSalvo);
        
        cin >> option;

        cout<<"\033c";

        switch (option){

            case 1:
            numeroMapa = escolherMapa();

            carregarMapa(numeroMapa, m, blocos, px, py);
            
            orientacao = 0;
            movimentos = 0;
            rotacoes = 0;
            jogoSalvo = false;
            
            jogar(m, blocos, numeroMapa, px, py, orientacao, movimentos, rotacoes, jogoSalvo);
            break;

            case 2:
              if(jogoSalvo){
                jogar(m, blocos, numeroMapa, px, py, orientacao, movimentos, rotacoes, jogoSalvo);
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