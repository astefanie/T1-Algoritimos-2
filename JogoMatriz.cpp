#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

int getch(void) {
  return _getch();
  }

const int TAM = 21;

struct posicao{ 
  int lin;
  int col;
};

struct jogo{ 
  int cenario[TAM][TAM];
  int blocos[TAM][TAM];

  int n;
  int orientacao;

  posicao jogador;

  int movimentos;
  int rotacoes;

  int numeroMapa;

  string titulo;
};

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



bool carregarMapa(int numeroMapa, jogo &j, string &motivo){

  string nomeArquivo = "mapa" + to_string(numeroMapa) + ".csv";

  ifstream arquivo(nomeArquivo);

  if(!arquivo.is_open()){
    motivo = "Arquivo não encontrado.";
    return false;
  }

  string linha;

  if(!getline(arquivo, linha)){
    motivo = "Dimensão ausente.";
    return false;
  }

  j.n = stoi(linha);

  if(j.n < 11 || j.n > TAM){
    motivo = "Dimensão fora do intervalo permitido.";
    return false;
  }

  if(!getline(arquivo, j.titulo)){
    motivo = "Titulo ausente.";
    return false;
  }

  for(int l = 0; l < TAM; l++){
    for(int c = 0; c < TAM; c++){
        j.blocos[l][c] = 0;
    }
  }

  for(int l = 0; l < j.n; l++){

    if(!getline(arquivo, linha)){
      motivo = "Quantidade de linhas menor que a dimensão.";
      return false;
    }

    stringstream ss(linha);

    for(int c = 0; c < j.n; c++){

      string valorTexto;

      if(!getline(ss, valorTexto, ',')){
        motivo = "Quantidade de colunas incorreta.";
        return false;
      }

      int valor = stoi (valorTexto);

      if(valor == 2){

        j.jogador.lin = l;
        j.jogador.col = c;

        j.cenario[l][c] = 0;
      }
      else if(valor == 3){

        j.blocos[l][c] = 1;
        j.cenario[l][c] = 0;
      }
      else{

        j.cenario[l][c] = valor;
      }
    }
  }

  j.numeroMapa = numeroMapa;

  return true;
}

bool portaEstaFechada(int celula, int orientacao){
  
  if (celula == 6){

    if(orientacao == 0 || orientacao == 2){
      return true;
    }

    return false;
  }
    
  if (celula == 7){

    if(orientacao == 1 || orientacao == 3){
      return true;
    } 

    return false;
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

void moverJogador(jogo &j, char tecla){
  int proxLin = j.jogador.lin;
  int proxCol = j.jogador.col;

  switch (tecla){ //switch que faz o jogador poder se mover

    case 'w':
    case 'W': {
      proxLin = j.jogador.lin - 1; 
      break;
    }
    case 's':
    case 'S': {
      proxLin = j.jogador.lin + 1;
      break;
    }
    case 'a':
    case 'A': {
      proxCol = j.jogador.col - 1;
      break;
    }
    case 'd':
    case 'D': {
      proxCol = j.jogador.col + 1;
      break;
    }
  }
  if(j.blocos[proxLin][proxCol] == 0 && daPraPassar(j.cenario[proxLin][proxCol], j.orientacao)){
    
    j.jogador.lin = proxLin; //atualiza as coordenadas
    j.jogador.col = proxCol; //atualiza as coordenadas

    j.movimentos++; //soma um movimento 
    }
}

void girarMatriz(jogo &j, char tecla){
  
  int novaLin;
  int novaCol;

  int aux[TAM][TAM];
  int auxBlocos[TAM][TAM];
  
  for(int l = 0; l < j.n; l++){

    for(int c = 0; c < j.n; c++){

      if(tecla == 'e' || tecla == 'E'){
        
        aux[c][j.n - 1 - l] = j.cenario[l][c]; //logica matematica utilizada para girar a matriz 
        auxBlocos[c][j.n - 1 - l] = j.blocos[l][c];
      }

      else if(tecla == 'q' or tecla == 'Q'){

        aux[j.n - 1 - c][l] = j.cenario[l][c];
        auxBlocos[j.n - 1 - c][l] = j.blocos[l][c];
      }
    }
  }

  for(int l = 0; l < j.n; l++){

    for(int c = 0; c < j.n; c++){

      j.cenario[l][c] = aux[l][c]; //loop que atualiza a matriz do jogo após girar ela 
      j.blocos[l][c] = auxBlocos[l][c];
    }
  }
  if(tecla == 'e' || tecla == 'E'){

    novaLin = j.jogador.col; //atualiza a orientação em graus da matriz 
    novaCol = j.n - 1 - j.jogador.lin;

    j.orientacao = (j.orientacao + 1) % 4;
  } 
  else if(tecla == 'q' || tecla == 'Q'){

    novaLin = j.n - 1 - j.jogador.col; //atualiza a orientação em graus da matriz
    novaCol = j.jogador.lin;

    j.orientacao = (j.orientacao + 3) % 4;
  }

  j.jogador.lin = novaLin;
  j.jogador.col - novaCol;

  j.rotacoes++; //aumenta a contagem de rotações
}

void esmagamento(jogo &j){

  for(int l = 0; l < j.n; l++){

    for(int c = 0; c < j.n; c++){

      if(j.blocos[l][c] == 1){

        if((j.cenario[l][c]==6 || j.cenario[l][c]==7) && portaEstaFechada(j.cenario[l][c], j.orientacao)){
          
          j.blocos[l][c] = 0;
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

bool aplicaGravidade(jogo &j){

    for (int l= j.n - 2; l >= 0; l--){

        for (int c = 0; c < j.n; c++){

            if(j.blocos[l][c] == 1){

                int linha = l;

                while(linha + 1 < j.n && j.blocos[linha + 1][c] == 0 && !sustentaBloco(j.cenario[linha + 1][c], j.orientacao)){

                    j.blocos[linha][c] = 0;
                    j.blocos[linha + 1][c] = 1;

                    linha ++;

                    if (linha == j.jogador.lin && c == j.jogador.col){

                      return true;
                    }
                }
            }
        }
    }

    return false;
}

char jogadorAlavanca(const jogo &j){
    
    if(j.cenario[j.jogador.lin][j.jogador.col] == 4){
        return 'T';
    }

    return '@';
}

void desenharCenario(const jogo &j){

  cout << "Mapa: " << j.numeroMapa << endl;
  cout << "Titulo: " << j.titulo << endl;

  cout << "Orientação: " << j.orientacao * 90 << "°" << endl;

  cout << "Movimentos: " << j.movimentos << endl;
  cout << "Rotações: " << j.rotacoes << endl;

  for(int l = 0; l < j.n; l++){

    for(int c = 0; c < j.n; c++){
        
        if(l == j.jogador.lin && c == j.jogador.col){

            cout << jogadorAlavanca(j) << " ";
        }
        
        else if(j.blocos[l][c] == 1){
            cout << "O ";
        } 
        
        else{

          switch (j.cenario[l][c]){

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
              if(portaEstaFechada(6, j.orientacao)){
              cout << "= ";
          }
          else{
            cout << ": ";
          }

          break;

          case 7:
            if(portaEstaFechada(7, j.orientacao)){
              cout << "| ";
            }
            else{
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

bool jogadorNaAlavanca(const jogo &j){

  return j.cenario[j.jogador.lin][j.jogador.col] == 4;
}

bool venceu(const jogo &j){

    if(j.cenario[j.jogador.lin][j.jogador.col] == 5){
        return true;
    }

    return false;
}

bool jogadorEsmagado(const jogo &j){

  int celula = j.cenario[j.jogador.lin][j.jogador.col];

    if ((celula == 7 || celula == 6) && portaEstaFechada(celula, j.orientacao)){

            return true;
    }

    return false;
}

void jogar(jogo &j, bool &jogoSalvo){

    char tecla;

    while(true) {

        cout << "\033c";

        desenharCenario(j);

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

            continue;
        }

        if (tecla == 'W' || tecla == 'w' || tecla == 'A' || tecla == 'a' || tecla == 'S' || tecla == 's' || tecla == 'D' || tecla == 'd') {

            moverJogador(j, tecla);

            if(venceu(j)){

              jogoSalvo = false;

              cout << "\033c";
                
              desenharCenario(j);

              cout << "\n====Você venceu!====\n";

              getch();

              break;
           }
        } 
        else if( tecla == 'q' || tecla == 'Q' || tecla == 'e' || tecla == 'E') {
            
            if (jogadorNaAlavanca(j)) {
                
                girarMatriz(j, tecla);

                if(jogadorEsmagado(j)){

                    cout << "\033c";
                    
                    cout << "==== Você foi esmagado pela porta! ====\n";
            
                    getch();

                    continue;
                }

                esmagamento(j);
                
                if(aplicaGravidade(j)){

                  cout << "\033c";

                  cout << "==== Você foi esmagado por um bloco! ====\n";

                  getch();

                  continue;
                }
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