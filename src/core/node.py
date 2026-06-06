from enum import Enum

class Color(Enum):
    RED = True
    BLACK = False

class Node:
    def __init__(self, key, value=None):
        """
        Inicializa um nó para a Árvore Rubro-Negra.
        
        :param key: A chave de ordenação. No nosso sistema de transações, será o PREÇO.
        :param value: O conteúdo do nó. Pode ser o objeto da Ordem (quantidade, id, etc).
        """
        self.key = key
        self.value = value
        
        # PROPRIEDADE FUNDAMENTAL: Todo nó inserido na árvore nasce VERMELHO.
        self.color = Color.RED
        
        # Ponteiros de navegação da árvore
        self.left = None    # Filho à esquerda
        self.right = None   # Filho à direita
        self.parent = None  # Referência ao pai

    def __repr__(self):
        """Método auxiliar para nos ajudar a printar o nó no console durante os testes"""
        return f"Node(Preço: {self.key}, Cor: {self.color.name})"