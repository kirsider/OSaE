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

    def pre_order(self, node):
        if node:
            self.pre_order(node.left)
            print(node.value)
            self.pre_order(node.right)
            


tree = BinaryTree(10)
tree.add(1)
tree.add(100)
tree.pre_order(tree.root)