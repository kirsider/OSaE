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


    def get_min_node(self, node: TreeNode):
        current = node
        
        while current.left is not None:
            current = current.left
        
        return current


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
        if self.root is None:
            self.root = TreeNode(value)
            return
        self.__add(self.root, value)


    def __remove(self, node: TreeNode, value: int):
        if node is None:
            return node

        if value < node.value:
            node.left = self.__remove(node.left, value)
        elif value > node.value:
            node.right = self.__remove(node.right, value)
        else:
            if node.left is None:
                tmp = node.right
                node = None
                return tmp
            elif node.right is None:
                tmp = node.left
                node = None
                return tmp

            tmp = self.get_min_node(node.right)
            node.value = tmp.value
            node.right = self.__remove(node.right, tmp.value)

        return node


    def remove(self, value: int):
        self.__remove(self.root, value)

    
    def __clear(self, node):
        if node:
            self.__clear(node.left)
            self.__clear(node.right)
            self.remove(node.value)
         
    def clear(self):
        self.__clear(self.root)
        self.root = None

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
tree.add(5)
tree.add(3)
tree.add(7)
tree.add(15)
tree.add(13)
tree.add(18)
tree.in_order(tree.root)
print("")

tree.remove(10)
tree.remove(3)
tree.in_order(tree.root)
print("")

tree.clear()
tree.in_order(tree.root)
print("")

tree.add(4)
tree.add(2)
tree.add(6)
tree.in_order(tree.root)