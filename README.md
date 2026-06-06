# Sistema Interativo de Placar de Jogadores
Número da Lista: Trabalho 29 - Árvores <br>
Conteúdo da Disciplina: Árvores Binárias de Busca Balanceadas <br>

## Alunas
|Matrícula | Aluno |
| -- | -- |
| 241025327  | Matheus Eiki Kimura Rezende|

## Sobre 
Este repositório contém o desenvolvimento de um **Sistema Interativo de Placar de Jogadores** desenvolvido inteiramente em **C**. 

O núcleo do projeto é uma **Árvore Rubro-Negra (Red-Black Tree)** implementada do zero, utilizada para armazenar e ordenar os jogadores com base em suas pontuações. O objetivo principal é demonstrar de forma visual e prática os conceitos de balanceamento de árvores binárias de busca através dos 5 cenários clássicos de reparo por rotação (esquerda/direita) e recolorização de nós. A aplicação conta com um menu interativo no terminal capaz de registrar novos usuários, exibir o ranking geral de pontuação e renderizar a estrutura interna da árvore de forma gráfica e legível, facilitando o acompanhamento do balanceamento $O(\log n)$ a cada inserção.

## Como Funciona o Sistema

O sistema utiliza o conceito de Árvore Rubro-Negra para gerenciar o placar de maneira eficiente. Cada jogador inserido é tratado como um nó na árvore, contendo seu nome e sua pontuação. A ordenação e o balanceamento da estrutura utilizam a pontuação como chave principal.

Para garantir que a árvore permaneça balanceada — ou seja, que a sua altura não cresça de forma desordenada e prejudique o desempenho —, o código monitora cada inserção. Todo novo jogador entra inicialmente como um nó **Vermelho**. A partir daí, o algoritmo verifica as propriedades da árvore e executa um dos **5 casos de reparo**:

* **Caso 1:** Se o nó for a raiz, ele é pintado de **Preto**.
* **Caso 2:** Se o pai do novo nó já for **Preto**, nenhuma regra é violada e a inserção termina.
* **Caso 3:** Se o pai e o tio do nó forem **Vermelhos**, ambos são recoloridos para **Preto** e o avô passa a ser **Vermelho**, transferindo a análise para o topo.
* **Caso 4 e Caso 5:** Se o tio for **Preto** (ou nulo), o algoritmo identifica se o nó está em uma posição interna ou externa e aplica **rotações geométricas (Esquerda/Direita)** junto com a troca de cores, trazendo o equilíbrio de volta ao sistema de forma imediata.

---

## Como Compilar e Rodar

Por ser um projeto escrito em C puro e sem dependências externas, você pode compilá-lo em qualquer sistema operacional (Linux, macOS ou Windows) que possua um compilador C instalado (como o `gcc`).

### Compilação
Abra o seu terminal na pasta onde o arquivo `main.c` está salvo e execute o seguinte comando para compilar:

```bash
gcc main.c -o placar
```

## Execução
Após a compilação bem-sucedida, um arquivo executável chamado placar será gerado. Para rodá-lo, utilize o comando correspondente ao seu sistema operacional:

No Linux ou macOS:
```bash
./placar
```

No Windows (Prompt de Comando ou PowerShell):
```bash
.\placar.exe
```
## Como Testar o Balanceamento
Para ver o comportamento dinâmico e o balanceamento O(logn) funcionando na prática, siga este roteiro de testes através do menu interativo do terminal:

Inicie o programa: O sistema já inicia com 3 jogadores de teste bem distribuídos (Alice com 40, Bob com 20 e Carlos com 60). Acesse a Opção 3 para ver a estrutura inicial perfeitamente simétrica.

Provoque um desbalanceamento (Caso 5): Escolha a Opção 1 e adicione um jogador com a pontuação 70. Em seguida, adicione outro com a pontuação 80. Se essa fosse uma árvore binária comum, ela criaria uma linha reta para a direita.

Verifique a rotação: Acesse a Opção 3 novamente. Você notará que o nó de valor 70 subiu na hierarquia, tornando-se o pai de 60 e 80. O programa aplicou automaticamente uma Rotação à Esquerda e ajustou as cores para Preto e Vermelho, demonstrando visualmente o sucesso do rebalanceamento automático.

Consulte o Ranking: Acesse a Opção 2 a qualquer momento para garantir que, independentemente de quantas rotações tenham acontecido nos bastidores, o percurso In-Order continua listando todos os jogadores perfeitamente ordenados do menor placar para o maior.
