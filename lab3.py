# Задание
# 
# 3.3.3. Создать двоичное дерево, хранящее числа. Каждый элемент дерева должен хранить число 
# и «левую» и «правую» ссылки на нижестоящие элементы. Необходимо реализовать алгоритмы добавления 
# числа в двоичное дерево и удаления числа из него. Пользователю должны быть доступны следующие 
# функции: добавить число, удалить число, очистить дерево, показать содержимое дерева на экране. 
# При выводе на экран показывать дерево в виде строки вида: содержимое родителя (содержимое левой 
# ветви, содержимое правой ветви); для каждой из ветвей функция вывода должна быть вызвана рекурсивно.


class TreeNode:
    left = None
    right = None
    value = 0

    def __init__(self, value: int):
        self.value = value


class BinaryTree:
    def __init__(self, root_value: int):
        self.root = TreeNode(root_value)

    def __add(self, node: TreeNode, value: int):
        if value > node.value:
            if node.right is None:
                node.right = TreeNode(value)
            else:
                self.__add(node.right, value)
        else:
            if node.left is None:
                node.left = TreeNode(value)
            else:
                self.__add(node.left, value)

    def add(self, value: int):
        self.__add(self.root, value)

    def in_order(self, node):
        if node:
            self.in_order(node.left)
            print(node.value)
            self.in_order(node.right)

    def pre_order(self, node):
        if node:
            print(node.value)
            self.pre_order(node.left)
            self.pre_order(node.right)
    
    def post_order(self, node):
        if node:
            self.post_order(node.left)
            self.post_order(node.right)
            print(node.value)
            


tree = BinaryTree(10)
tree.add(1)
tree.add(100)
tree.pre_order(tree.root)
tree.post_order(tree.root)