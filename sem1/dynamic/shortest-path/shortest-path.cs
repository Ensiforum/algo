using System;
using System.Collections.Generic;
using System.ComponentModel;
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

        private void DFS(Node node, List<Node> ts)
        {
            node.visited = true;
            foreach (var path in node.paths)
            {
                if (!path.to.visited)
                {
                    DFS(path.to, ts);
                }
            }
            ts.Add(node);
        }

        private List<Node> TopologicSort()
        {
            List<Node> ts = new List<Node>();
            foreach (var node in nodes)
            {
                if (!node.visited)
                {
                    DFS(node, ts);
                }
            }

            ts.Reverse();
            return ts;
        }

        public int MinDist(int from, int to)
        {
            if (from < 0 || from >= nodes.Count || to < 0 || to >= nodes.Count)
            {
                throw new ArgumentException();
            }

            int[] d = new int[nodes.Count];
            for (int i = 0; i < d.Length; i++)
            {
                d[i] = Int32.MaxValue;
            }

            d[from] = 0;
            var ts = TopologicSort();

            foreach (var node in ts)
            {
                foreach (var path in node.paths)
                {
                    d[path.to.index] = Math.Min(d[path.to.index], d[node.index] + path.cost);
                }
            }

            foreach (var node in nodes)
            {
                node.visited = false;
            }

            return d[to];
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