from __future__ import annotations

import random
from dataclasses import dataclass

'''
TODO
Сделать функцию и декоратор для модификации на отрезке
'''
ANSWER_BY_DEFAULT = 0


@dataclass
class Node:
    '''
    Приоритет - A[i], приоритеты упорядочены от малого к большему
    Если минимальных A[i] несколько, то берем любой
    '''
    key: int
    priority: int
    value: int
    left: 'typing.Any' = None
    right: 'typing.Any' = None

    answer: int = ANSWER_BY_DEFAULT

    def __repr__(self):
        s = f'({self.key}, {self.priority}, {self.value}, {self.answer}, left:{self.left}, right:{self.right})'
        return s

    def print_as_list(self):
        if self.left is not None:
            self.left.print_as_list()
        print(self.key, end=' ')
        if self.right is not None:
            self.right.print_as_list()


def update(tree: Node) -> Node | None:
    if not tree:
        return None
    try:
        tree.answer = get_answer(tree.left) + get_answer(tree.right) + tree.value
    except:
        print(tree)
    return tree


def update_decorator(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        if result is not None:
            if type(result) is tuple:
                for node in result:
                    update(node)
            else:
                update(result)
        return result
    return wrapper


# чтобы не вставлять внутри функции вызовы update, просто декорируем(?) функцию, чтобы декоратор сам вызывал update
# в результате чего, сам код внутри функции остался прежним
@update_decorator
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


@update_decorator
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


@update_decorator
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
    for i, item in enumerate(items):
        tree = insert_2(tree, Node(i, random.randint(0, len(items)), value=item, answer=item))
    return tree


# не работает, так как не сохраняет свойство двоичного дерева поиска :), пофиксите или используйте treapify_1
def treapify_2(items: list) -> Node:
    #items = sorted(items, reverse=True)
    queue = [Node(i, random.randint(0, len(items)), item, answer=item) for i, item in enumerate(items)][::-1]
    while len(queue) > 1:
        queue.append(merge(queue.pop(0), queue.pop(0)))
    return queue[0]


def get_answer(tree: Node) -> int:
    if not tree:
        return ANSWER_BY_DEFAULT
    return tree.answer

# индексация начинается с 1, правая граница включена
def get_result(tree: Node, left: int, right: int) -> int:
    if not tree:
        return ANSWER_BY_DEFAULT
    left -= 2
    right -= 1
    tree_left, tree = split(tree, left)
    tree, tree_right  = split(tree, right)
    print(tree)
    result = get_answer(tree)
    tree = merge(tree_left, tree)
    tree = merge(tree, tree_right)
    return result
