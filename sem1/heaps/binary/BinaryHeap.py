class BinaryHeap:
    def __init__(self):
        self.H = [None]

    def size(self):
        return len(self.H) - 1

    def __repr__(self):
        return str(self.H[1:])

    def satisfies_assertions(self):
        for i in range(2, len(self.H)):
            assert self.H[i] >= self.H[i // 2], \
            f'Min heap property fails at position {i // 2}, parent elt: {self.H[i // 2]}, child elt: {self.H[i]}'

    def min_element(self):
        return self.H[1]

    def bubble_up(self, index):
        assert index >= 1
        if index == 1:
            return
        parent_index = index // 2
        if self.H[parent_index] < self.H[index]:
            return
        else:
            self.H[parent_index], self.H[index] = self.H[index], self.H[parent_index]
            self.bubble_up(parent_index)

    def bubble_down(self, index):
        assert 0 <= index < len(self.H)
        
        lchild_index = 2 * index
        rchild_index = 2 * index + 1
        
        lchild_value = self.H[lchild_index] if lchild_index < len(self.H) else float('inf')
        rchild_value = self.H[rchild_index] if rchild_index < len(self.H) else float('inf')
        
        if self.H[index] <= min(lchild_value, rchild_value):
            return
        
        min_child_value, min_child_index = min((lchild_value, lchild_index), (rchild_value, rchild_index))
        self.H[index], self.H[min_child_index] = self.H[min_child_index], self.H[index]
        self.bubble_down(min_child_index)

    def insert(self, elt):
        self.H.append(elt)
        self.bubble_up(self.size())

    def delete_min(self):
        self.H[0], self.H[len(self.H) - 1] = self.H[len(self.H) - 1], self.H[0]
        self.H.pop()
        self.bubble_down(0)
        
def TestBinHeap():
    h = BinaryHeap()
    print('Inserting: 5, 2, 4, -1 and 7 in that order.')
    h.insert(5)
    print(f'\t Heap = {h}')
    assert(h.min_element() == 5)
    h.insert(2)
    print(f'\t Heap = {h}')
    assert(h.min_element() == 2)
    h.insert(4)
    print(f'\t Heap = {h}')
    assert(h.min_element() == 2)
    h.insert(-1)
    print(f'\t Heap = {h}')
    assert(h.min_element() == -1)
    h.insert(7)
    print(f'\t Heap = {h}')
    assert(h.min_element() == -1)
    h.satisfies_assertions()

    print('Deleting minimum element')
    h.delete_min()
    print(f'\t Heap = {h}')
    assert(h.min_element() == 2)
    h.delete_min()
    print(f'\t Heap = {h}')
    assert(h.min_element() == 4)
    h.delete_min()
    print(f'\t Heap = {h}')
    assert(h.min_element() == 5)
    h.delete_min()
    print(f'\t Heap = {h}')
    assert(h.min_element() == 7)
    # Test delete_max on heap of size 1, should result in empty heap.
    h.delete_min()
    print(f'\t Heap = {h}')
    print('All tests passed!')


TestBinHeap()

# Resources: 
# Materials from the following coursera course were used, but with my realisation of some methods^
# https://www.coursera.org/learn/algorithms-searching-sorting-indexing
