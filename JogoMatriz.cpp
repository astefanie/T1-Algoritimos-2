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
    {1,2,4,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1}
};

      for(int l = 0; l < TAM; l++){
        for(int c = 0; c < TAM; c++){
          m[l][c] = temp[l][c]; //colocando o mapa "temporario" no do jogo
        }
      }

      blocos[7][5] = 1;
      blocos[5][6] = 1;

      px = 9; //jogador no mapa 2
      py = 1;
      break;
      }

    case 3:{
      int temp[TAM][TAM] = {
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

      blocos[2][6] = 1;
      blocos[4][6] = 1;
      blocos[6][4] = 1;
      blocos[8][8] = 1;

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

void moverJogador(int m[][TAM], int blocos[][TAM], int &px, int &py, int &elementoAbaixo, int orientacao, int &movimentos, char tecla){
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
  int aux[TAM][TAM];
  int auxBlocos[TAM][TAM];
  
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
      if(tecla == 'e' or tecla == 'E'){
        aux[c][TAM - 1 - l] = m[l][c]; //logica matematica utilizada para girar a matriz 
        auxBlocos[c][TAM - 1 - l] = blocos[l][c];
      }
      else if(tecla == 'q' or tecla == 'Q'){
        aux[TAM - 1 - c][l] = m[l][c];
        auxBlocos[TAM - 1 - c][l] = blocos[l][c];
      }
    }
  }
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
      m[l][c] = aux[l][c]; //loop que atualiza a matriz do jogo após girar ela 
      blocos[l][c] = auxBlocos[l][c];
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

void esmagamento(int m[][TAM], int blocos[][TAM], int orientacao){
  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){

      if(blocos[l][c] == 1){
        if((m[l][c]==6 || m[l][c]==7) && portaEstaFechada(m[l][c], orientacao)){
            blocos[l][c] = 0;
        }
      }
    }
  }
}
bool sustentaBloco(int celula, int orientacao){
  if(celula == 1){
    return true;
  }
  else if(celula == 7 || celula == 6){
    return portaEstaFechada(celula, orientacao);
  }
  return false;
}

void gravidade(int m[][TAM], int blocos[][TAM], int orientacao){

    for (int l= TAM-2; l>= 0; l--){
        for (int c = 0; c < TAM; c++){
            if(blocos[l][c] == 1){
                int linha = l;

                while(linha + 1 < TAM && blocos[linha + 1][c] == 0 && sustentaBloco(m[linha + 1][c], orientacao) == false) {
                    blocos[linha][c] = 0;
                    blocos[linha + 1][c] = 1;

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
        
        if(blocos[l][c] == 1){
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
        if (tecla == 'r' || tecla == 'R'){
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
                cout << "\033c";
                
                desenharCenario(m, blocos, numeroMapa, orientacao, movimentos, rotacoes);

            cout << "\n====Você venceu!====\n";

            getch();
            break;
           }
        
        } else if( tecla == 'q' || tecla == 'Q' || tecla == 'e' || tecla == 'E') {
            
            if (jogadorNaAlavanca(elementoAbaixo)) {
                
                girarMatriz(m, blocos, px, py, elementoAbaixo, orientacao, rotacoes, tecla);

                esmagamento(m, blocos, orientacao);
                
                gravidade(m, blocos, orientacao);
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
            numeroMapa = escolherMapa();

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