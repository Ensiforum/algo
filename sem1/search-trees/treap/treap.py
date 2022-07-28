import random
from dataclasses import dataclass


@dataclass
class Node:
    '''
    Приоритет - A[i], приоритеты упорядочены от малого к большему
    Если минимальных A[i] несколько, то берем любой
    '''
    key: int
    priority: int
    left: 'typing.Any' = None
    right: 'typing.Any' = None

    def __repr__(self):
        s = f'({self.key}, {self.priority}, left:{self.left}, right:{self.right})'
        return s

    def print_as_list(self):
        if self.left is not None:
            self.left.print_as_list()
        print(self.key, end=' ')
        if self.right is not None:
            self.right.print_as_list()


def split(tree: Node, key) -> (Node, Node):
    if tree is None:
        return None, None
    if key >= tree.key:
        tree_1, tree_2 = split(tree.right, key)
        tree.right = tree_1
        return tree, tree_2
    else:
        tree_1, tree_2 = split(tree.left, key)
        tree.left = tree_2
        return tree_1, tree


def merge(tree_left, tree_right):
    if not tree_left:
        return tree_right
    if not tree_right:
        return tree_left

    if tree_left.priority > tree_right.priority:
        tree_left.right = merge(tree_left.right, tree_right)
        return tree_left
    else:
        tree_right.left = merge(tree_left, tree_right.left)
        return tree_right


def insert_1(tree: Node, new_node: Node) -> Node:
    if not tree:
        return new_node
    tree_1, tree_2 = split(tree, new_node.key)
    tree_1 = merge(tree_1, new_node)

    tree = merge(tree_1, tree_2)
    return tree


def insert_2(tree: Node, new_node: Node) -> Node:
    if not tree:
        return new_node
    if new_node.priority > tree.priority:
        new_node.left, new_node.right = split(tree, new_node.key)
        return new_node
    if new_node.key < tree.key:
        tree.left = insert_2(tree.left, new_node)
    else:
        tree.right = insert_2(tree.right, new_node)
    return tree


def union(tree_1: Node, tree_2: Node) -> Node:
    if not tree_1:
        return tree_2
    if not tree_2:
        return tree_1

    if tree_1.priority < tree_2.priority:
        tree_1, tree_2 = tree_2, tree_1

    tree_2_left, tree_2_right = split(tree_2, tree_1.key)

    result = tree_1
    result.left = union(tree_1.left, tree_2_left)
    result.right = union(tree_1.right, tree_2_right)

    return result


def treapify_1(items: list) -> Node:
    tree = None
    for item in items:
        tree = insert_2(tree, Node(item, random.randint(0, len(items))))
    return tree


def treapify_2(items: list) -> Node:
    items = sorted(items, reverse=True)
    queue = [Node(item, random.randint(0, len(items))) for item in items]
    while len(queue) > 1:
        queue.append(merge(queue.pop(0), queue.pop(0)))
    return queue[0]
