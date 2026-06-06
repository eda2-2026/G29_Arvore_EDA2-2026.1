from src.core.node import Node, Color

class RedBlackTree:
    def __init__(self):
        # A raiz da árvore começa como None (vazia).
        self.root = None

    def insert(self, key, value=None):
        new_node = Node(key, value)
        
        # CASO 1: A árvore está vazia
        if self.root is None:
            self.root = new_node
            # Regra fundamental 2 da Árvore Rubro-Negra: A raiz deve ser sempre PRETA.
            self.root.color = Color.BLACK
            return new_node
            
        # CASO 2 
        current = self.root
        parent = None
        
        while current is not None:
            parent = current
            # Se a nova chave for menor, vamos para a esquerda
            if key < current.key:
                current = current.left
            # Se for maior ou igual, vamos para a direita
            # (Em um Order Book, múltiplos pedidos podem ter o mesmo preço)
            else:
                current = current.right
                
        # Vincula o ponteiro de pai do novo nó ao nó onde a busca parou
        new_node.parent = parent
        
        # Insere o novo nó como filho esquerdo ou direito do pai
        if key < parent.key:
            parent.left = new_node
        else:
            parent.right = new_node
            
        return new_node

    def inorder_walk(self, node):
        """
        Método auxiliar para ler a árvore em ordem crescente (In-Order Traversal).
        Excelente para testar se a nossa BST está ordenando corretamente.
        """
        res = []
        if node:
            res.extend(self.inorder_walk(node.left))
            res.append((node.key, node.color.name))
            res.extend(self.inorder_walk(node.right))
        return res
    
    def left_rotate(self, x):
        """
        Rotaciona o nó x para a esquerda.
        O filho da direita de x (chamado de y) se torna o novo pai de x.
        """
        y = x.right
        if y is None:
            return  # Não dá para rotacionar se não houver filho à direita
        
        # 1. Transforma a subárvore esquerda de y na subárvore direita de x
        x.right = y.left
        if y.left is not None:
            y.left.parent = x
            
        # 2. Atualiza o pai de y para ser o pai de x
        y.parent = x.parent
        
        # 3. Se x era a raiz, y vira a nova raiz da árvore
        if x.parent is None:
            self.root = y
        # Se x era um filho da esquerda, atualiza o pai para apontar para y
        elif x == x.parent.left:
            x.parent.left = y
        # Se x era um filho da direita, atualiza o pai para apontar para y
        else:
            x.parent.right = y
            
        # 4. Coloca x como filho esquerdo de y
        y.left = x
        x.parent = y

    def right_rotate(self, y):
        """
        Rotaciona o nó y para a direita (Operação espelho da rotação à esquerda).
        O filho da esquerda de y (chamado de x) se torna o novo pai de y.
        """
        x = y.left
        if x is None:
            return  # Não dá para rotacionar se não houver filho à esquerda
            
        # 1. Transforma a subárvore direita de x na subárvore esquerda de y
        y.left = x.right
        if x.right is not None:
            x.right.parent = y
            
        # 2. Atualiza o pai de x para ser o pai de y
        x.parent = y.parent
        
        # 3. Se y era a raiz, x vira a nova raiz
        if y.parent is None:
            self.root = x
        elif y == y.parent.right:
            y.parent.right = x
        else:
            y.parent.left = x
            
        # 4. Coloca y como filho direito de x
        x.right = y
        y.parent = x