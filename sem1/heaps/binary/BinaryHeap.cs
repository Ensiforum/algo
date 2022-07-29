using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace algo
{
    public class BinaryHeap<T> : IEnumerable<T> where T : IComparable<T>
    {
        private readonly List<T> _heap;
        
        public BinaryHeap()
        {
            _heap = new List<T>();
        }

        public BinaryHeap(IEnumerable<T> list)
        {
            _heap = new List<T>();
            _heap.AddRange(list);
            Heapify();
        }

        private void SiftDown(int currentElementIndex)
        {
            int leftChildIndex = currentElementIndex * 2 + 1;
            int rightChildIndex = currentElementIndex * 2 + 2;

            if (leftChildIndex > _heap.Count)
            {
                return;
            }

            var minValue = rightChildIndex > _heap.Count ? 
                _heap[leftChildIndex] : 
                FindMin(_heap[leftChildIndex], _heap[rightChildIndex]);

            if (minValue.CompareTo(_heap[currentElementIndex]) > 0)
            {
                return;
            }

            if (minValue.CompareTo(_heap[leftChildIndex]) == 0)
            {
                Swap(currentElementIndex, leftChildIndex);
                SiftDown(leftChildIndex);
            }
            else
            {
                Swap(currentElementIndex, rightChildIndex);
                SiftDown(rightChildIndex);
            }
        }

        private void SiftUp(int currentElementIndex)
        {
            if (_heap.Count <= 1)
            {
                return;
            }
            
            int parentIndex = (currentElementIndex - 1) / 2;

            if (_heap[currentElementIndex].CompareTo(_heap[parentIndex]) >= 0)
            {
                return;
            }
            
            Swap(currentElementIndex, parentIndex);
            SiftUp(parentIndex);
        }

        private void Heapify()
        {
            int middle = (_heap.Count - 2) / 2;

            for (int i = middle; i >= 0; i--)
            {
                SiftDown(i);
            }
        }

        private static T FindMin(T first, T second)
        {
            return first.CompareTo(second) >= 0 ? first : second;
        }

        private void Swap(int first, int second)
        {
            T temp = _heap[first];
            _heap[first] = _heap[second];
            _heap[second] = temp;
        }

        public T this[int index]
        {
            get
            {
                if (index < 0 || index >= _heap.Count)
                {
                    throw new IndexOutOfRangeException();
                }
                return _heap[index];
            }
        }

        public void Merge(BinaryHeap<T> otherHeap)
        {
            _heap.AddRange(otherHeap._heap);
            Heapify();
        }

        public T ExtractMin()
        {
            T min = _heap[0];

            _heap[0] = _heap.Last();
            _heap.RemoveAt(_heap.Count - 1);
            SiftDown(0);

            return min;
        }

        public void Insert(T value)
        {
            _heap.Add(value);
            SiftUp(_heap.Count - 1);
        }

        public IEnumerator<T> GetEnumerator()
        {
            return ((IEnumerable<T>) _heap).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public override string ToString()
        {
            if (_heap.Count == 0)
            {
                return "[]";
            }
            
            StringBuilder sb = new StringBuilder();
            sb.Append("[");
            foreach (var elem in _heap)
            {
                sb.Append(elem + ", ");
            }

            sb.Remove(sb.Length - 2, 2);
            sb.Append("]");
            return sb.ToString();
        }
    }
}
