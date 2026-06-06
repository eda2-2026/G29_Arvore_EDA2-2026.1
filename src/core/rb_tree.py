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