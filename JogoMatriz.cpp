#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstdio>
#include <conio.h>
#include <windows.h>
using namespace std;

const int TAM = 21;
const int MAX_RECORDES = 200;

const int EM_JOGO = 0;
const int VITORIA = 1;
const int DERROTA = 2;

struct Posicao {
    int lin;
    int col;
};

struct Jogo {
    int cenario[TAM][TAM];
    int blocos[TAM][TAM];
    int n;
    int orientacao;
    Posicao jogador;
    int movimentos;
    int rotacoes;
    int numeroMapa;
    string titulo;
};

struct Recorde {
    string nome;
    int mapa;
    int movimentos;
    int rotacoes;
};

struct Resultado {
    int estado;
    int posicao;
    int total;
    string mensagem;
};

template <typename T>
void trocar(T &a, T &b) {
    T aux = a;
    a = b;
    b = aux;
}

string numeroTexto(int numero) {
    stringstream texto;
    texto << numero;
    return texto.str();
}

bool converterInt(string texto, int &valor) {
    stringstream leitor(texto);

    if (!(leitor >> valor)) {
        return false;
    }

    char sobra;
    if (leitor >> sobra) {
        return false;
    }

    return true;
}

char minuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return char(c - 'A' + 'a');
    }
    return c;
}

bool teclaDeJogo(char tecla) {
    tecla = minuscula(tecla);

    return tecla == 'w' || tecla == 'a' || tecla == 's' ||
           tecla == 'd' || tecla == 'q' || tecla == 'e';
}

bool dentro(const Jogo &jogo, int l, int c) {
    return l >= 0 && c >= 0 && l < jogo.n && c < jogo.n;
}

// Movimentacao, portas, giros e gravidade
bool portaEstaFechada(int celula, int orientacao) {
    if (celula == 6 && orientacao % 2 == 0) {
        return true;
    }

    if (celula == 7 && orientacao % 2 == 1) {
        return true;
    }

    return false;
}

bool sustentaBloco(int celula, int orientacao) {
    return celula == 1 || portaEstaFechada(celula, orientacao);
}

bool daPraPassar(int celula, int orientacao) {
    if (celula == 0 || celula == 4 || celula == 5) {
        return true;
    }

    if (celula == 6 || celula == 7) {
        return !portaEstaFechada(celula, orientacao);
    }

    return false;
}

bool jogadorNaAlavanca(const Jogo &jogo) {
    return jogo.cenario[jogo.jogador.lin][jogo.jogador.col] == 4;
}

bool venceu(const Jogo &jogo) {
    return jogo.cenario[jogo.jogador.lin][jogo.jogador.col] == 5;
}

bool jogadorEsmagado(const Jogo &jogo) {
    return portaEstaFechada(jogo.cenario[jogo.jogador.lin][jogo.jogador.col], jogo.orientacao);
}

void moverJogador(Jogo &jogo, char tecla) {
    int proximaLinha = jogo.jogador.lin;
    int proximaColuna = jogo.jogador.col;

    tecla = minuscula(tecla);

    if (tecla == 'w') {
        proximaLinha--;
    }
    else if (tecla == 's') {
        proximaLinha++;
    }
    else if (tecla == 'a') {
        proximaColuna--;
    }
    else if (tecla == 'd') {
        proximaColuna++;
    }
    else {
        return;
    }

    if (dentro(jogo, proximaLinha, proximaColuna) &&
        jogo.blocos[proximaLinha][proximaColuna] == 0 &&
        daPraPassar(jogo.cenario[proximaLinha][proximaColuna], jogo.orientacao)) {

        jogo.jogador.lin = proximaLinha;
        jogo.jogador.col = proximaColuna;

        if (jogo.movimentos < INT_MAX) {
            jogo.movimentos++;
        }
    }
}

void girarMatriz(Jogo &jogo, char tecla) {
    tecla = minuscula(tecla);

    if (tecla != 'q' && tecla != 'e') {
        return;
    }

    int matrizAux[TAM][TAM] = {};
    int blocosAux[TAM][TAM] = {};

    for (int l = 0; l < jogo.n; l++) {
        for (int c = 0; c < jogo.n; c++) {
            int novaLinha = c;
            int novaColuna = jogo.n - 1 - l;

            if (tecla == 'q') {
                novaLinha = jogo.n - 1 - c;
                novaColuna = l;
            }

            matrizAux[novaLinha][novaColuna] = jogo.cenario[l][c];
            blocosAux[novaLinha][novaColuna] = jogo.blocos[l][c];
        }
    }

    for (int l = 0; l < jogo.n; l++) {
        for (int c = 0; c < jogo.n; c++) {
            jogo.cenario[l][c] = matrizAux[l][c];
            jogo.blocos[l][c] = blocosAux[l][c];
        }
    }

    Posicao posicaoAnterior = jogo.jogador;

    if (tecla == 'e') {
        jogo.jogador.lin = posicaoAnterior.col;
        jogo.jogador.col = jogo.n - 1 - posicaoAnterior.lin;
        jogo.orientacao = (jogo.orientacao + 1) % 4;
    }
    else {
        jogo.jogador.lin = jogo.n - 1 - posicaoAnterior.col;
        jogo.jogador.col = posicaoAnterior.lin;
        jogo.orientacao = (jogo.orientacao + 3) % 4;
    }

    if (jogo.rotacoes < INT_MAX) {
        jogo.rotacoes++;
    }
}

void esmagamento(Jogo &jogo) {
    for (int l = 0; l < jogo.n; l++) {
        for (int c = 0; c < jogo.n; c++) {
            if (portaEstaFechada(jogo.cenario[l][c], jogo.orientacao)) {
                jogo.blocos[l][c] = 0;
            }
        }
    }
}

bool aplicaGravidade(Jogo &jogo) {
    // Se o bloco cair na posicao do jogador, ele perde.
    for (int l = jogo.n - 2; l >= 0; l--) {
        for (int c = 0; c < jogo.n; c++) {
            if (jogo.blocos[l][c] == 1) {
                int linha = l;

                while (linha + 1 < jogo.n &&
                       jogo.blocos[linha + 1][c] == 0 &&
                       !sustentaBloco(jogo.cenario[linha + 1][c], jogo.orientacao)) {

                    jogo.blocos[linha][c] = 0;
                    linha++;
                    jogo.blocos[linha][c] = 1;

                    if (linha == jogo.jogador.lin && c == jogo.jogador.col) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool mapaEstavel(Jogo jogo) {
    Jogo original = jogo;
    aplicaGravidade(jogo);

    for (int l = 0; l < jogo.n; l++) {
        for (int c = 0; c < jogo.n; c++) {
            if (jogo.blocos[l][c] != original.blocos[l][c]) {
                return false;
            }
        }
    }

    return true;
}

int processaTecla(Jogo &jogo, char tecla) {
    tecla = minuscula(tecla);

    if (tecla == 'q' || tecla == 'e') {
        if (jogadorNaAlavanca(jogo)) {
            girarMatriz(jogo, tecla);

            if (jogadorEsmagado(jogo)) {
                return DERROTA;
            }

            esmagamento(jogo);

            if (aplicaGravidade(jogo)) {
                return DERROTA;
            }
        }
    }
    else {
        moverJogador(jogo, tecla);
    }

    if (venceu(jogo)) {
        return VITORIA;
    }

    return EM_JOGO;
}
// Leitura: os dados so substituem o destino depois de conferidos.
// Leitura dos arquivos de mapa e solucao
bool lerLinha(ifstream &arquivo, string &linha) {
    if (!getline(arquivo, linha)) {
        return false;
    }
    if (!linha.empty() && linha.back() == '\r') {
        linha.erase(linha.size() - 1);
    }
    return true;
}

bool separar(string linha, string campos[], int quantidade) {
    stringstream leitor(linha);

    if (linha.empty() || linha.back() == ',') {
        return false;
    }

    for (int i = 0; i < quantidade; i++) {
        if (!getline(leitor, campos[i], ',')) {
            return false;
        }
    }

    string sobra;
    return !getline(leitor, sobra, ',');
}

bool tituloValido(string titulo) {
    return titulo.find_first_not_of(" \t\r\n") != string::npos && titulo.find(',') == string::npos;
}

bool lerMatriz(ifstream &arquivo, int matriz[][TAM], int tamanho, int maximo, string &motivo) {
    string linha, campos[TAM];
    for (int l = 0;l<tamanho;l++) {
        if (!lerLinha(arquivo, linha)) {
            motivo = "Faltam linhas na matriz.";
            return false;
        }
        if (!separar(linha, campos, tamanho)) {
            motivo = "Quantidade de colunas incorreta na linha " + numeroTexto(l + 1) + ".";
            return false;
        }
        for (int c = 0;c<tamanho;c++) {
            if (!converterInt(campos[c], matriz[l][c]) || matriz[l][c]<0 || matriz[l][c]>maximo) {
                motivo = "Valor invalido na linha " + numeroTexto(l + 1) + ", coluna " + numeroTexto(c + 1) + ".";
                return false;
            }
        }
    }
    return true;
}

bool fimArquivo(ifstream &arquivo, string &motivo) {
    string sobra;
    if (lerLinha(arquivo, sobra)) {
        motivo = "Linhas extras no arquivo.";
        return false;
    }
    if (arquivo.bad()) {
        motivo = "Falha de leitura.";
        return false;
    }
    return true;
}

bool lerMapa(int numeroMapa, Jogo &jogo, string &motivo) {
    string nomeArquivo = "mapa" + numeroTexto(numeroMapa) + ".csv";
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        motivo = "Arquivo nao encontrado.";
        return false;
    }

    Jogo mapaLido = {};
    string linha;

    if (!lerLinha(arquivo, linha) ||
        !converterInt(linha, mapaLido.n) ||
        mapaLido.n < 11 || mapaLido.n > TAM) {
        motivo = "Dimensao ausente ou invalida (11 a 21).";
        return false;
    }

    if (!lerLinha(arquivo, mapaLido.titulo) || !tituloValido(mapaLido.titulo)) {
        motivo = "Titulo ausente, vazio ou com virgula.";
        return false;
    }

    if (!lerMatriz(arquivo, mapaLido.cenario, mapaLido.n, 7, motivo) ||
        !fimArquivo(arquivo, motivo)) {
        return false;
    }

    int quantidadeJogadores = 0;
    int quantidadeSaidas = 0;

    for (int l = 0; l < mapaLido.n; l++) {
        for (int c = 0; c < mapaLido.n; c++) {
            int celula = mapaLido.cenario[l][c];

            if (celula == 2) {
                quantidadeJogadores++;
                mapaLido.jogador.lin = l;
                mapaLido.jogador.col = c;
                mapaLido.cenario[l][c] = 0;
            }
            else if (celula == 3) {
                mapaLido.blocos[l][c] = 1;
                mapaLido.cenario[l][c] = 0;
            }
            else if (celula == 5) {
                quantidadeSaidas++;
            }
        }
    }

    if (quantidadeJogadores != 1) {
        motivo = "O mapa precisa de exatamente um jogador.";
        return false;
    }

    if (quantidadeSaidas == 0) {
        motivo = "Mapa sem saida.";
        return false;
    }

    mapaLido.numeroMapa = numeroMapa;
    jogo = mapaLido;
    motivo = "";
    return true;
}
// Coordena leitura e validacao, sem mudar as regras nem imprimir.
bool carregarMapa(int numeroMapa, Jogo &jogo, string &motivo) {
    Jogo mapaLido = {};
    if (!lerMapa(numeroMapa, mapaLido, motivo)) {
        return false;
    }
    if (!mapaEstavel(mapaLido)) {
        motivo = "Mapa instavel: bloco sem apoio.";
        return false;
    }
    jogo = mapaLido;
    return true;
}

int descobrirQuantidadeMapas() {
    int numero = 1;
    while (numero<INT_MAX) {
        ifstream arquivo("mapa" + numeroTexto(numero) + ".csv");
        if (!arquivo.is_open()) {
            break;
        }
        numero++;
    }
    return numero-1;
}

string lerTituloMapa(int numeroMapa) {
    ifstream arquivo("mapa" + numeroTexto(numeroMapa) + ".csv");
    string dimensao, titulo;
    if (lerLinha(arquivo, dimensao) && lerLinha(arquivo, titulo) && tituloValido(titulo)) return titulo;
    return "Titulo indisponivel";
}

bool lerSolucao(int numeroMapa, string &teclas, string &motivo) {
    ifstream arquivo("mapa" + numeroTexto(numeroMapa) + ".sol");
    if (!arquivo.is_open()) {
        motivo = "Arquivo .sol inexistente.";
        return false;
    }
    if (!lerLinha(arquivo, teclas)) {
        motivo = "Arquivo .sol vazio.";
        return false;
    }
    return fimArquivo(arquivo, motivo);
}

bool validarTeclas(string teclas, Resultado &resultado) {
    resultado.estado = EM_JOGO;
    resultado.posicao = 0;
    resultado.total = int(teclas.size());

    for (int i = 0; i < resultado.total; i++) {
        if (!teclaDeJogo(teclas[i])) {
            resultado.posicao = i + 1;
            resultado.mensagem = "Tecla invalida na posicao " + numeroTexto(i + 1) + ".";
            return false;
        }
    }

    return true;
}

Resultado executarSolucao(Jogo &jogo, string teclas) {
    Resultado resultado = {};

    if (!validarTeclas(teclas, resultado)) {
        return resultado;
    }

    for (int i = 0; i < resultado.total; i++) {
        resultado.posicao = i + 1;
        resultado.estado = processaTecla(jogo, teclas[i]);

        if (resultado.estado != EM_JOGO) {
            break;
        }
    }

    if (resultado.estado == VITORIA) {
        resultado.mensagem = "Solucao valida.";
    }
    else if (resultado.estado == DERROTA) {
        resultado.mensagem = "Derrota na tecla " + numeroTexto(resultado.posicao) + ".";
    }
    else {
        resultado.mensagem = "As teclas acabaram sem chegar a saida.";
    }

    return resultado;
}

// Gravacao e recuperacao da partida
bool validarSalvo(const Jogo &jogo, string &motivo) {
    if (jogo.n < 11 || jogo.n > TAM ||
        jogo.numeroMapa < 1 ||
        jogo.orientacao < 0 || jogo.orientacao > 3 ||
        jogo.movimentos < 0 || jogo.rotacoes < 0 ||
        !tituloValido(jogo.titulo) ||
        !dentro(jogo, jogo.jogador.lin, jogo.jogador.col)) {

        motivo = "Cabecalho do jogo salvo invalido.";
        return false;
    }

    int quantidadeSaidas = 0;

    for (int l = 0; l < jogo.n; l++) {
        for (int c = 0; c < jogo.n; c++) {
            int celula = jogo.cenario[l][c];

            if (celula < 0 || celula > 7 ||
                celula == 2 || celula == 3 ||
                jogo.blocos[l][c] < 0 || jogo.blocos[l][c] > 1 ||
                (jogo.blocos[l][c] && sustentaBloco(celula, jogo.orientacao))) {

                motivo = "Matrizes do jogo salvo invalidas.";
                return false;
            }

            if (celula == 5) {
                quantidadeSaidas++;
            }
        }
    }

    int linha = jogo.jogador.lin;
    int coluna = jogo.jogador.col;

    if (quantidadeSaidas == 0 || jogo.blocos[linha][coluna] ||
        !daPraPassar(jogo.cenario[linha][coluna], jogo.orientacao) ||
        venceu(jogo)) {
        motivo = "Posicao do jogador ou saida invalida.";
        return false;
    }

    if (!mapaEstavel(jogo)) {
        motivo = "Jogo salvo com blocos instaveis.";
        return false;
    }

    return true;
}

void escreverMatriz(ofstream &arquivo, const int matriz[][TAM], int tamanho) {
    for (int l = 0;l<tamanho;l++) {
        for (int c = 0;c<tamanho;c++) {
            if (c) arquivo << ',';
            arquivo << matriz[l][c];
        }
        arquivo << '\n';
    }
}

bool gravarSalvo(const Jogo &jogo, string &motivo) {
    ofstream arquivo("jogo_salvo.tmp", ios::trunc);
    if (!arquivo.is_open()) {
        motivo = "Nao foi possivel criar o jogo salvo.";
        return false;
    }
    arquivo << "LABIRINTO_M2_V1\n" << jogo.n << ',' << jogo.numeroMapa << ',' << jogo.orientacao << ',' << jogo.jogador.lin << ',' << jogo.jogador.col << ',' << jogo.movimentos << ',' << jogo.rotacoes << '\n';
    arquivo << jogo.titulo << '\n';
    escreverMatriz(arquivo, jogo.cenario, jogo.n);
    escreverMatriz(arquivo, jogo.blocos, jogo.n);
    arquivo.close();
    if (arquivo.fail()) {
        motivo = "Falha ao gravar. O salvo anterior foi preservado.";
        return false;
    }
    if (!MoveFileExA("jogo_salvo.tmp", "jogo_salvo.csv", MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)) {
        motivo = "Nao foi possivel substituir jogo_salvo.csv.";
        return false;
    }
    motivo = "";
    return true;
}

bool salvarJogo(const Jogo &jogo, string &motivo) {
    return validarSalvo(jogo, motivo) && gravarSalvo(jogo, motivo);
}

bool lerSalvo(Jogo &jogo, string &motivo) {
    ifstream arquivo("jogo_salvo.csv");

    if (!arquivo.is_open()) {
        motivo = "Sem jogo salvo.";
        return false;
    }

    Jogo jogoLido = {};
    string linha;
    string campos[7];

    if (!lerLinha(arquivo, linha) || linha != "LABIRINTO_M2_V1" ||
        !lerLinha(arquivo, linha) || !separar(linha, campos, 7) ||
        !converterInt(campos[0], jogoLido.n) ||
        !converterInt(campos[1], jogoLido.numeroMapa) ||
        !converterInt(campos[2], jogoLido.orientacao) ||
        !converterInt(campos[3], jogoLido.jogador.lin) ||
        !converterInt(campos[4], jogoLido.jogador.col) ||
        !converterInt(campos[5], jogoLido.movimentos) ||
        !converterInt(campos[6], jogoLido.rotacoes) ||
        jogoLido.n < 11 || jogoLido.n > TAM ||
        !lerLinha(arquivo, jogoLido.titulo)) {

        motivo = "Cabecalho do jogo salvo corrompido.";
        return false;
    }

    if (!lerMatriz(arquivo, jogoLido.cenario, jogoLido.n, 7, motivo) ||
        !lerMatriz(arquivo, jogoLido.blocos, jogoLido.n, 1, motivo) ||
        !fimArquivo(arquivo, motivo)) {
        return false;
    }

    jogo = jogoLido;
    return true;
}

bool carregarJogoSalvo(Jogo &jogo, string &motivo) {
    Jogo jogoLido = {};
    if (!lerSalvo(jogoLido, motivo) || !validarSalvo(jogoLido, motivo)) return false;
    jogo = jogoLido;
    return true;
}

bool existeJogoSalvoValido() {
    Jogo jogo = {};
    string motivo;
    return carregarJogoSalvo(jogo, motivo);
}

bool invalidarSalvo(string &motivo) {
    if (DeleteFileA("jogo_salvo.csv")) {
        return true;
    }
    if (GetLastError() == ERROR_FILE_NOT_FOUND) {
        return true;
    }
    motivo = "Nao foi possivel apagar o jogo salvo.";
    return false;
}

// Ranking de recordes
bool nomeValido(string nome) {
    return nome.size() <= 15 && tituloValido(nome);
}

bool melhor(const Recorde &primeiro, const Recorde &segundo) {
    if (primeiro.movimentos < segundo.movimentos) {
        return true;
    }

    if (primeiro.movimentos == segundo.movimentos &&
        primeiro.rotacoes < segundo.rotacoes) {
        return true;
    }

    return false;
}

void ordenarRecordes(Recorde registros[], int quantidade) {
    for (int i = 1; i < quantidade; i++) {
        for (int j = i; j > 0 && melhor(registros[j], registros[j - 1]); j--) {
            trocar(registros[j], registros[j - 1]);
        }
    }
}

bool registrarRecorde(const Recorde &recorde, string &motivo) {
    bool faltaQuebra = false;
    ifstream anterior("recordes.csv", ios::binary);
    if (anterior.is_open()) {
        anterior.seekg(0, ios::end);
        if (anterior.tellg()>0) {
            anterior.seekg(-1, ios::end);
            char ultimo;
            anterior.get(ultimo);
            faltaQuebra = ultimo != '\n';
        }
        anterior.close();
    }
    ofstream arquivo("recordes.csv", ios::app);
    if (!arquivo.is_open()) {
        motivo = "Nao foi possivel abrir recordes.csv.";
        return false;
    }
    if (faltaQuebra) {
        arquivo << '\n';
    }
    arquivo << recorde.nome << ',' << recorde.mapa << ',' << recorde.movimentos << ',' << recorde.rotacoes << '\n';
    arquivo.close();
    if (arquivo.fail()) {
        motivo = "Falha ao gravar o recorde.";
        return false;
    }
    return true;
}

bool carregarRecordes(int mapa, Recorde registros[], int &quantidade, string &motivo) {
    quantidade = 0;
    motivo = "";

    ifstream arquivo("recordes.csv");
    if (!arquivo.is_open()) {
        motivo = "Sem arquivo de recordes disponivel.";
        return false;
    }

    string linha;
    string campos[4];
    int invalidos = 0;

    while (lerLinha(arquivo, linha)) {
        Recorde recorde = {};

        if (!separar(linha, campos, 4) || !nomeValido(campos[0]) ||
            !converterInt(campos[1], recorde.mapa) ||
            !converterInt(campos[2], recorde.movimentos) ||
            !converterInt(campos[3], recorde.rotacoes) ||
            recorde.mapa < 1 || recorde.movimentos < 0 || recorde.rotacoes < 0) {

            invalidos++;
            continue;
        }

        recorde.nome = campos[0];

        if (recorde.mapa != mapa) {
            continue;
        }

        if (quantidade < MAX_RECORDES) {
            registros[quantidade] = recorde;
            quantidade++;
        }
        else {
            int pior = 0;

            for (int i = 1; i < quantidade; i++) {
                if (melhor(registros[pior], registros[i])) {
                    pior = i;
                }
            }

            if (melhor(recorde, registros[pior])) {
                registros[pior] = recorde;
            }
        }
    }

    if (invalidos > 0) {
        motivo = numeroTexto(invalidos) + " linha(s) invalida(s) ignorada(s).";
    }

    if (arquivo.bad()) {
        motivo = "Falha de leitura dos recordes.";
        return false;
    }

    return true;
}
// Tela e entrada. ESC cancela inclusive as perguntas dos menus.
// Desenho, teclado e menus
void limparTela() {
    system("cls");
}

void voltarInicioTela(){

    COORD inicio = {0, 0};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), inicio);
}

int lerTecla() {
    int teclaLida = _getch();
    if (teclaLida == 0 || teclaLida == 224) {
        _getch();
        return 0;
    }
    return teclaLida;
}

void pausa() {
    cout << "\nPressione uma tecla...";
    lerTecla();
}

bool lerTexto(string &texto, int limite) {
    texto = "";
    while (true) {
        int teclaLida = lerTecla();
        if (teclaLida == 27) {
            cout << '\n';
            return false;
        }
        if (teclaLida == 13) {
            cout << '\n';
            return true;
        }
        if (teclaLida == 8 && !texto.empty()) {
            texto.erase(texto.size()-1);
            cout << "\b \b";
        }
        else if (teclaLida >= 32 && teclaLida <= 126 && int(texto.size())<limite) {
            texto+=char(teclaLida);
            cout << char(teclaLida);
        }
    }
}

int pedirNumero(string pergunta) {
    while (true) {
        cout << pergunta << " (ESC volta): ";
        string texto;
        int numero;
        if (!lerTexto(texto, 12)) return -1;
        if (converterInt(texto, numero) && numero >= 0) return numero;
        cout << "Digite um numero valido.\n";
    }
}

bool confirmar(string pergunta) {
    cout << pergunta << " [S/N; ESC cancela]\n";
    while (true) {
        int teclaLida = lerTecla();
        if (teclaLida == 's' || teclaLida == 'S') return true;
        if (teclaLida == 'n' || teclaLida == 'N' || teclaLida == 27) return false;
    }
}

void FundoAzul() {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

void CorNormal() {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void desenharCenario(const Jogo &jogo) {
    cout << "Mapa " << jogo.numeroMapa << " - " << jogo.titulo << endl;
    cout << "Orientacao: " << jogo.orientacao * 90 << " graus" << endl;
    cout << "Movimentos: " << jogo.movimentos << endl;
    cout << "Rotacoes: " << jogo.rotacoes << "\n\n";

    for (int l = 0; l < jogo.n; l++) {
        for (int c = 0; c < jogo.n; c++) {
            int celula = jogo.cenario[l][c];
            char simbolo = ' ';

            if (l == jogo.jogador.lin && c == jogo.jogador.col) {
                if (celula == 4) simbolo = 'T';
                else simbolo = '@';
            }
            else if (jogo.blocos[l][c] == 1) {
                simbolo = 'O';
            }
            else if (celula == 1) {
                simbolo = '#';
            }
            else if (celula == 4) {
                simbolo = 'A';
            }
            else if (celula == 5) {
                simbolo = 'S';
            }
            else if (celula == 6) {
                if (portaEstaFechada(celula, jogo.orientacao)) simbolo = '=';
                else simbolo = ':';
            }
            else if (celula == 7) {
                if (portaEstaFechada(celula, jogo.orientacao)) simbolo = '|';
                else simbolo = ';';
            }

            if(simbolo == '#'){
                FundoAzul();
                cout << "  ";
                CorNormal();
            }
            else{
                cout << simbolo << ' ';
            }
        }
        cout << endl;
    }
}

void exibirResultado(const Jogo &jogo, const Resultado &resultado) {
    cout << resultado.mensagem << " Teclas no arquivo: " << resultado.total << "; executadas: " << resultado.posicao << "; movimentos: " << jogo.movimentos << "; rotacoes: " << jogo.rotacoes << '\n';
}

int escolherMapa(bool aleatorio) {
    int quantidadeMapas = descobrirQuantidadeMapas();

    if (quantidadeMapas == 0) {
        cout << "Nenhum mapa encontrado.\n";
        pausa();
        return -1;
    }

    int quantidadeValidos = 0;

    for (int i = 1; i <= quantidadeMapas; i++) {
        Jogo jogo = {};
        string motivo;

        if (carregarMapa(i, jogo, motivo)) {
            cout << i << " - " << jogo.titulo << endl;
            quantidadeValidos++;
        }
        else {
            cout << i << " - " << lerTituloMapa(i)
                 << " - [INDISPONIVEL] " << motivo << endl;
        }
    }

    if (quantidadeValidos == 0) {
        cout << "Nenhum mapa valido.\n";
        pausa();
        return -1;
    }

    while (true) {
        int numeroEscolhido;

        if (aleatorio) {
            numeroEscolhido = pedirNumero("Mapa (0 = aleatorio)");
        }
        else {
            numeroEscolhido = pedirNumero("Mapa");
        }

        if (numeroEscolhido == -1) {
            return -1;
        }

        if (numeroEscolhido == 0 && aleatorio) {
            int sorteado = rand() % quantidadeValidos;

            for (int i = 1; i <= quantidadeMapas; i++) {
                Jogo jogo = {};
                string motivo;

                if (carregarMapa(i, jogo, motivo)) {
                    if (sorteado == 0) {
                        return i;
                    }
                    sorteado--;
                }
            }

            cout << "Os arquivos mudaram. Abra a lista novamente.\n";
            pausa();
            return -1;
        }

        Jogo jogo = {};
        string motivo;

        if (numeroEscolhido >= 1 && numeroEscolhido <= quantidadeMapas &&
            carregarMapa(numeroEscolhido, jogo, motivo)) {
            return numeroEscolhido;
        }

        cout << "Mapa indisponivel. " << motivo << endl;
    }
}

void registrarVitoria(const Jogo &jogo) {
    string motivo;

    if (!invalidarSalvo(motivo)) {
        cout << motivo << " O salvo antigo ainda existe.\n";
    }

    cout << "Voce venceu!\n";

    Recorde recorde = {};
    recorde.mapa = jogo.numeroMapa;
    recorde.movimentos = jogo.movimentos;
    recorde.rotacoes = jogo.rotacoes;

    while (true) {
        cout << "Nome (1 a 15 caracteres sem virgula; ESC pula o recorde): ";

        if (!lerTexto(recorde.nome, 15)) {
            return;
        }

        if (nomeValido(recorde.nome)) {
            break;
        }

        cout << "Nome invalido.\n";
    }

    if (registrarRecorde(recorde, motivo)) {
        cout << "Recorde registrado.\n";
    }
    else {
        cout << motivo << endl;
    }

    pausa();
}

void jogar(Jogo jogo) {
    
    limparTela();
    
    while (true) {
        voltarInicioTela();
        desenharCenario(jogo);

        int tecla = lerTecla();
        string motivo;

        if (tecla == 27) {
            if (salvarJogo(jogo, motivo)) {
                return;
            }

            cout << motivo << "\nO arquivo salvo anterior, se houver, nao foi substituido.\n";

            if (confirmar("Voltar ao menu sem salvar o progresso atual?")) {
                return;
            }
            continue;
        }

        if (minuscula(char(tecla)) == 'r') {
            Jogo inicial = {};

            if (carregarMapa(jogo.numeroMapa, inicial, motivo)) {
                jogo = inicial;
            }
            else {
                cout << "Nao foi possivel reiniciar: " << motivo << endl;
                pausa();
            }
            continue;
        }

        int estado = processaTecla(jogo, char(tecla));

        if (estado == VITORIA) {
            limparTela();
            desenharCenario(jogo);
            registrarVitoria(jogo);
            return;
        }

        if (estado == DERROTA) {
            cout << "Voce foi esmagado por uma porta ou bloco. A fase sera reiniciada.\n";
            pausa();

            if (!carregarMapa(jogo.numeroMapa, jogo, motivo)) {
                cout << motivo << endl;
                invalidarSalvo(motivo);
                pausa();
                return;
            }
        }
    }
}

void novoJogo() {
    int numeroMapa = escolherMapa(true);

    if (numeroMapa < 1) {
        return;
    }

    Jogo jogo = {};
    string motivo;

    if (!carregarMapa(numeroMapa, jogo, motivo)) {
        cout << motivo << endl;
        pausa();
        return;
    }

    if (existeJogoSalvoValido() && !confirmar("Substituir a partida salva?")) {
        return;
    }

    if (!invalidarSalvo(motivo)) {
        cout << motivo << endl;
        pausa();
        return;
    }

    jogar(jogo);
}

void continuarJogo() {
    Jogo jogo = {};
    string motivo;

    if (carregarJogoSalvo(jogo, motivo)) {
        jogar(jogo);
    }
    else {
        cout << "Sem jogo salvo valido. " << motivo << endl;
        pausa();
    }
}

void reproduzirSolucao(Jogo jogo, string teclas) {
    Resultado resultado = {};

    if (!validarTeclas(teclas, resultado)) {
        exibirResultado(jogo, resultado);
        pausa();
        return;
    }

    limparTela();
    desenharCenario(jogo);

    for (int i = 0; i < resultado.total; i++) {
        cout << "\nReproducao: tecla " << i + 1 << "/" << resultado.total
             << " = " << teclas[i]
             << ". Pressione uma tecla para avancar\n ESC volta.\n";

        if (lerTecla() == 27) {
            return;
        }

        resultado.posicao = i + 1;
        resultado.estado = processaTecla(jogo, teclas[i]);

        limparTela();
        desenharCenario(jogo);

        if (resultado.estado != EM_JOGO) {
            break;
        }
    }

    if (resultado.estado == VITORIA) {
        resultado.mensagem = "Solucao valida (nao entra nos recordes).";
    }
    else if (resultado.estado == DERROTA) {
        resultado.mensagem = "Derrota na tecla " + numeroTexto(resultado.posicao) + ".";
    }
    else {
        resultado.mensagem = "As teclas acabaram sem chegar a saida.";
    }

    exibirResultado(jogo, resultado);
    pausa();
}

void verificarTodos() {
    int quantidade = descobrirQuantidadeMapas();

    if (quantidade == 0) {
        cout << "Nenhum mapa encontrado." << endl;
    }

    for (int i = 1; i <= quantidade; i++) {
        if (_kbhit() && lerTecla() == 27) {
            return;
        }

        Jogo jogo = {};
        string motivo;
        string teclas;

        cout << "Mapa " << i << ": ";

        if (!carregarMapa(i, jogo, motivo)) {
            cout << lerTituloMapa(i) << " - INDISPONIVEL - " << motivo << endl;
            continue;
        }

        cout << jogo.titulo << " - ";

        if (!lerSolucao(i, teclas, motivo)) {
            cout << motivo << endl;
            continue;
        }

        Resultado resultado = executarSolucao(jogo, teclas);
        exibirResultado(jogo, resultado);
    }

    pausa();
}

void menuSolucoes() {
    int opcao = pedirNumero("1 = Reproduzir um mapa; 2 = Verificar todos");

    if (opcao == 2) {
        verificarTodos();
        return;
    }

    if (opcao != 1) {
        return;
    }

    int numeroMapa = escolherMapa(false);
    if (numeroMapa < 1) {
        return;
    }

    Jogo jogo = {};
    string motivo;
    string teclas;

    if (!carregarMapa(numeroMapa, jogo, motivo) ||
        !lerSolucao(numeroMapa, teclas, motivo)) {
        cout << motivo << endl;
        pausa();
        return;
    }

    reproduzirSolucao(jogo, teclas);
}

void mostrarRecordes() {
    int mapa = pedirNumero("Numero do mapa para consultar recordes");
    if (mapa < 1) {
        return;
    }

    Recorde registros[MAX_RECORDES];
    int quantidade;
    string motivo;

    bool conseguiuLer = carregarRecordes(mapa, registros, quantidade, motivo);

    if (!motivo.empty()) {
        cout << motivo << endl;
    }

    if (conseguiuLer) {
        ordenarRecordes(registros, quantidade);

        if (quantidade == 0) {
            cout << "Ainda nao ha recordes para este mapa.\n";
        }

        for (int i = 0; i < quantidade && i < 5; i++) {
            cout << i + 1 << ". " << registros[i].nome << " - "
                 << registros[i].movimentos << " movimentos, "
                 << registros[i].rotacoes << " rotacoes\n";
        }
    }

    pausa();
}

void sobre() {
    cout << "LABIRINTO GIRATORIO - M2" << endl;
    cout << "Equipe:" << endl;
    cout << "Stefanie Saffnauer" << endl;
    cout << "Joao Victor Atallah" << endl;
    cout << "Diogo Lucas" << endl;
    cout << "Outubro, 2026" << endl;
    cout << "Algoritmos e Programacao II - Professor Thiago Felski" << endl;

    cout << "\nO objetivo e chegar ate a saida (S)." << endl;
    cout << "W, A, S, D - movimentar o jogador" << endl;
    cout << "Q e E - girar a matriz quando estiver na alavanca" << endl;
    cout << "R - reiniciar a fase" << endl;
    cout << "ESC - salvar o jogo e voltar ao menu" << endl;
    cout << "\nParedes (#), blocos (O) e portas fechadas impedem a passagem." << endl;
    cout << "A representa a alavanca; T e o jogador sobre ela." << endl;
    cout << "Portas fecham dependendo da orientacao do mapa." << endl;
    cout << "Depois do giro, os blocos podem cair por causa da gravidade." << endl;
    cout << "Se um bloco cair sobre o jogador ou uma porta fechar sobre ele, a fase reinicia." << endl;

    pausa();
}

int menu() {
    limparTela();

    cout << "--- LABIRINTO GIRATORIO  ---" << endl;
    cout << "1 - Novo jogo" << endl;

    if (existeJogoSalvoValido()) {
        cout << "2 - Continuar" << endl;
    }

    cout << "3 - Ver solucao" << endl;
    cout << "4 - Recordes" << endl;
    cout << "5 - Sobre" << endl;
    cout << "6 - Fim" << endl;

    return pedirNumero("Opcao");
}

void executarOpcao(int opcao) {
    limparTela();

    switch (opcao) {
        case 1:
            novoJogo();
            break;
        case 2:
            continuarJogo();
            break;
        case 3:
            menuSolucoes();
            break;
        case 4:
            mostrarRecordes();
            break;
        case 5:
            sobre();
            break;
        case 6:
        case -1:
            break;
        default:
            cout << "Opcao invalida.\n";
            pausa();
    }
}

void EscondeCursor(){

    CONSOLE_CURSOR_INFO info;

    info.dwSize = 1;
    info.bVisible = FALSE;

    SetConsoleCursorInfo(
        GetStdHandle(STD_OUTPUT_HANDLE), &info
    );
}

void prepararConsole() {
    EscondeCursor();
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(unsigned(time(0)));
}

int main() {
    prepararConsole();
    int opcao;

    do {
        opcao = menu();
        executarOpcao(opcao);
    } while (opcao != 6);

    return 0;
}