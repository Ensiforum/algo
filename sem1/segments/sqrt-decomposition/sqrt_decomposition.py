import math

'''
Для примера использована функция суммы
'''


def build_blocks(a: list):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))

    blocks = [0] * block_size

    for i in range(n):
        blocks[i // block_size] += a[i]

    return blocks


def query(a: list, left: int, right: int, blocks: list[int], diff_blocks: list[int] = None):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))
    diff_blocks = diff_blocks or [0] * block_size
    left_block = (left - 1) // block_size
    right_block = (right + 1) // block_size
    result = 0

    for i in range(left, (left_block + 1) * block_size):
        result += a[i] + diff_blocks[left_block]
    for j in range(left_block + 1, right_block):
        result += blocks[j] + diff_blocks[j]
    for i in range(right_block * block_size, right + 1):
        result += a[i] + diff_blocks[right_block]
    return result


def set_value(a: list, index: int, value: int, blocks: list[int], diff_blocks: list[int] = None):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))
    diff_blocks = diff_blocks or [0] * block_size
    block = index // block_size
    blocks[block] += value - (a[index] + diff_blocks[block])
    a[index] = value - diff_blocks[block]


def plus_value_range(a: list, left: int, right: int, value: int, diff_blocks: list[int] = None):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))
    diff_blocks = diff_blocks or [0] * block_size
    left_block = (left - 1) // block_size
    right_block = (right + 1) // block_size
    for i in range(left, (left_block + 1) * block_size):
        a[i] += value
    for j in range(left_block + 1, right_block):
        diff_blocks[j] += value
    for i in range(right_block * block_size, right + 1):
        a[i] += value
    return diff_blocks


def value_at_i(a: list[int], i: int, dif_blocks: list[int]):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))
    block = i // block_size
    return a[i] + dif_blocks[block]
