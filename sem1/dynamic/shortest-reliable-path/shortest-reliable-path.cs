using System;
using System.Collections.Generic;
using System.Linq;

namespace algo
{
    public class Graph
    {
        private List<Node> nodes = new List<Node>();

        public Graph(int[,] adj, int unreachableValue)
        {
            if (adj.GetLength(0) != adj.GetLength(1))
            {
                throw new ArgumentException("Matrix is not a square");
            }

            for (int i = 0; i < adj.GetLength(0); i++)
            {
                nodes.Add(new Node(nodes.Count));
                nodes.Last().paths = new List<Path>();
            }
            
            for (int i = 0; i < adj.GetLength(0); i++)
            {
                for (int j = 0; j < adj.GetLength(1); j++)
                {
                    if (adj[i, j] != unreachableValue)
                    {
                        nodes[i].paths.Add(new Path(nodes[j], adj[i, j]));
                    }
                }
            }
        }

        public int GetMinReliableDist(int s, int t, int k)
        {
            int[,] d = new int[nodes.Count, k + 1];

            for (int i = 0; i < d.GetLength(0); i++)
            {
                for (int j = 0; j < d.GetLength(1); j++)
                {
                    d[i, j] = Int32.MaxValue;
                }
            }
            
            d[s, 0] = 0;
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < nodes.Count; j++)
                {
                    for (int n = 0; n < nodes[j].paths.Count; n++)
                    {
                        int m = nodes[j].paths[n].to.index;
                        d[m, i + 1] = Math.Min(
                            d[m, i + 1], 
                            d[j, i] + nodes[j].paths[n].cost < 0 ? 
                                Int32.MaxValue : 
                                d[j, i] + nodes[j].paths[n].cost
                        );
                    }
                }
            }

            return FindMinOnRow(d, t);
        }

        private static int FindMinOnRow(int[,] matrix, int rowIndex)
        {
            int min = Int32.MaxValue;
            for (int i = 0; i < matrix.GetLength(1); i++)
            {
                if (matrix[rowIndex, i] < min)
                {
                    min = matrix[rowIndex, i];
                }
            }

            return min;
        }

        private class Node
        {
            public List<Path> paths = new List<Path>();
            public bool visited = false;
            public int index;

            public Node(int index)
            {
                this.index = index;
            }
        }

        private class Path
        {
            public Node to;
            public int cost;

            public Path( Node to, int cost)
            {
                this.to = to;
                this.cost = cost;
            }
        }
    }
}