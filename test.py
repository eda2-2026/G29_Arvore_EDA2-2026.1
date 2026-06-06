from src.core.rb_tree import RedBlackTree

tree = RedBlackTree()
# Simulando a chegada de preços de ações
tree.insert(15)
tree.insert(10)
tree.insert(20)
tree.insert(8)
tree.insert(12)

# O output esperado deve ser os preços perfeitamente ordenados:
# [(8, 'RED'), (10, 'RED'), (12, 'RED'), (15, 'BLACK'), (20, 'RED')]
print(tree.inorder_walk(tree.root))