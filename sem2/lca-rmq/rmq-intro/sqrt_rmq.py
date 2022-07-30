import math


def build_blocks(a: list):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))

    blocks = [math.inf] * block_size

    for i in range(n):
        blocks[i // block_size] = min(blocks[i // block_size], a[i])

    return blocks


def query(a: list, left: int, right: int, blocks: list):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))
    left_block = (left - 1) // block_size
    right_block = (right + 1) // block_size
    result = math.inf

    for i in range(left, (left_block + 1) * block_size):
        result = min(result, a[i])
    for j in range(left_block + 1, right_block):
        result = min(result, blocks[j])
    for i in range(right_block * block_size, right + 1):
        result = min(result, a[i])
    return result


def set_value(a: list, index: int, value: int, blocks: list):
    n = len(a)
    block_size = math.ceil(math.sqrt(n))
    block = index // block_size
    a[index] = value
    for i in range(block * block_size, (block + 1) * block_size):
        blocks[block] = min(blocks[block], a[i])
