# T1-Algoritimos-2
# Labirinto Giratório — M2

**Disciplina:** Algoritmos e Programação II  
**Professor:** Thiago Felski

**Integrantes:**
- Stefanie Saffnauer
- João Victor Atallah
- Diogo Lucas

## 1. Ambiente de desenvolvimento

O jogo foi desenvolvido em **C++ para Windows**, utilizando o VS Code e o compilador g++.

## 2. Formato do arquivo de salvamento

Na M2, utilizamos o arquivo `jogo_salvo.csv` para guardar o progresso da partida, permitindo que o jogador continue de onde parou mesmo depois de fechar o programa.

O arquivo é organizado da seguinte forma:

- **Primeira linha:** identificação da versão (`LABIRINTO_M2_V1`).
- **Segunda linha:** tamanho do mapa, número do mapa, orientação, linha e coluna do jogador, quantidade de movimentos e rotações.
- **Terceira linha:** título do mapa.
- **Linhas seguintes:** matriz do cenário.
- **Últimas linhas:** matriz dos blocos.

As informações são separadas por vírgulas, e as matrizes são gravadas linha por linha.

Quando o jogador pressiona ESC, a partida é salva. Ao escolher Continuar, o programa lê o arquivo e recupera o estado anterior. Caso o arquivo esteja ausente ou inválido, a opção não fica disponível.

## 3. Comparação das funções da M1 com a M2

Na M1, várias funções recebiam muitos parâmetros separados. Na M2, passamos a utilizar a `struct Jogo`, que reúne as informações da partida e facilita a organização do código.

| Função | Assinatura na M1 | Assinatura na M2 | Motivo da mudança |
|---|---|---|---|
| Mover jogador | `void moverJogador(int m[][TAM], int blocos[][TAM], int &px, int &py, int orientacao, int &movimentos, char tecla)` | `void moverJogador(Jogo &jogo, char tecla)` | As informações necessárias agora estão reunidas na struct. |
| Girar matriz | `void girarMatriz(int m[][TAM], int blocos[][TAM], int &px, int &py, int &orientacao, int &rotacoes, char tecla)` | `void girarMatriz(Jogo &jogo, char tecla)` | Simplificamos a passagem dos dados necessários para a rotação. |
| Desenhar cenário | `void desenharCenario(int m[][TAM], int blocos[][TAM], int mapaAtual, int orientacao, int movimentos, int rotacoes, int px, int py)` | `void desenharCenario(const Jogo &jogo)` | A função recebe o estado do jogo sem precisar modificá-lo. |
| Gravidade | `void gravidade(int m[][TAM], int blocos[][TAM], int orientacao)` | `bool aplicaGravidade(Jogo &jogo)` | Além de movimentar os blocos, agora informa se o jogador foi esmagado. |
| Carregar mapa | `void carregarMapa(int numeroMapa, int m[][TAM], int blocos[][TAM], int &px, int &py)` | `bool carregarMapa(int numeroMapa, Jogo &jogo, string &motivo)` | Os mapas passaram a ser lidos de arquivos, com validação e identificação de erros. |
| Verificar alavanca | `bool jogadorNaAlavanca(int m[][TAM], int px, int py)` | `bool jogadorNaAlavanca(const Jogo &jogo)` | A posição do jogador pode ser consultada diretamente na struct. |

## 4. Defeitos corrigidos da M1

Durante a evolução do jogo, corrigimos os seguintes problemas:

- **Esmagamento:** na M1, um bloco podia parar sobre o jogador sem causar derrota. Agora, se um bloco cair na posição do personagem, a fase é reiniciada.
- **Limites da matriz:** adicionamos uma verificação para impedir que o jogador tente acessar uma posição fora do mapa.

Além dessas correções, passamos a validar os mapas carregados, evitando que arquivos ausentes ou com informações incorretas provoquem problemas durante o jogo.

## 5. Decisões de projeto

**Uso de structs:** decidimos guardar as informações da partida na `struct Jogo`, incluindo as matrizes, posição do personagem, orientação e contadores. Assim, evitamos passar muitos parâmetros separados entre as funções.

**Duas matrizes:** mantivemos uma matriz para o cenário e outra para os blocos. Isso permite que um bloco ocupe a posição de uma saída ou porta sem apagar o elemento original do mapa.

**Posição do jogador:** utilizamos uma `struct Posicao` dentro de `Jogo`. Dessa forma, o personagem pode ficar sobre a alavanca ou uma porta aberta sem alterar o conteúdo da célula.

**Gravidade:** percorremos a matriz de baixo para cima, para que os blocos caiam corretamente. Após cada rotação, verificamos primeiro o fechamento das portas, depois o esmagamento dos blocos e, por último, aplicamos a gravidade.

**Orientação:** utilizamos os valores de 0 a 3 para representar as quatro orientações possíveis do cenário, correspondentes a 0°, 90°, 180° e 270°.

**Arquivos de solução:** tanto o jogador quanto a reprodução dos arquivos `.sol` utilizam a função `processaTecla()`. Assim, as mesmas regras são aplicadas nas duas situações.

**Recordes:** decidimos ordenar os resultados pelo menor número de movimentos. Quando há empate, utilizamos a menor quantidade de rotações como critério de desempate.

## 6. Desafios extras

Não foram implementados os desafios extras opcionais propostos no enunciado. Nosso foco foi desenvolver e corrigir as funcionalidades obrigatórias da M2.