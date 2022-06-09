#include <vector>

// Дерево отрезков:
// Построение: O(n)
// Ответ на запрос: O(log n)
// Требует памяти: O(n)

// Запросы:
// Ассоциативная операция на подотрезке
// Изменение значения на подотрезке

// Данная реализация отличается от классической наличием у отрезков поля size
// Это позволяет легко создавать отрезки размера отличного от степени двойки
// Что позволяет не выделять лишнюю память для фиктивных подотрезков, но увеличивает количество памяти которое занимает каждый подотрезок

// Также позволяет создавать подотрезки с нессиметричными частями left и right, что может быть полезно

class Node {
private:
    int size;
    int min;
    Node* left;
    Node* right;
    
public:
    Node(int value) {
        size = 1;
        min = value;

        left = nullptr;
        right = nullptr;
    }

    Node(Node* left, Node* right) {
        this->left = left;
        this->right = right;
        
        size = left->size + right->size;
        min = std::min(left->min, right->min);
    }

    int GetMin(int leftBound, int rightBound) {
        int segmentSize = rightBound - leftBound + 1;
        
        // Нужен именно этот отрезок
        if (size == segmentSize) {
            return min;
        }
        
        int leftSize = left->size;
        
        // Нужный отрезок находится в правой части
        if (leftSize < leftBound) {
            return right->GetMin(leftBound - leftSize, rightBound - leftSize);
        } else {
            // Нужный отрезок находится в левой части
            if (leftSize >= rightBound) {
                return left->GetMin(leftBound, rightBound);
            } else {
            // Нужный отрезок "посередине"
                return std::min(left->GetMin(leftBound, leftSize),
                                right->GetMin(1, rightBound - leftSize));
            }
        }
    }
};

class SegmentTree {
private:
    Node* head;

    // Создание подотрезка на основе первого элемента и необходимой длины  
    Node* MakeNode(int32_t startIndex, int32_t width,
                   const std::vector<int32_t>& values) {
        Node* result;
        if (width == 1) {
            result = new Node(values[startIndex]);
        } else {
            result = new Node(MakeNode(startIndex, width - width / 2, values),
                              MakeNode(startIndex + width - width / 2, width / 2, values));
        }
        return result;
    }

public:
    SegmentTree(int size,
                const std::vector<int>& values) {
        head = MakeNode(0, size, values);
    }

    int GetMin(int leftBound, int rightBound) {
        head->GetMin(leftBound, rightBound);
    }
};


