using System;
using System.Collections.Generic;

public class bitonic_salesman
{
    private List<Point> _points = new List<Point>();
    private double[,] _dp;
    
    public void Add(int x, int y)
    {
        _points.Add(new Point(x, y));
    }

    private double Distance(int first, int second)
    {
        double xSquare = Math.Pow(_points[first].x - _points[second].x, 2);
        double ySquare = Math.Pow(_points[first].y - _points[second].y, 2);
        return Math.Sqrt(xSquare + ySquare);
    }

    private double FindTourDistance(int first, int second)
    {
        if (_dp[first, second] != -1)
        {
            return _dp[first, second];
        }

        _dp[first, second] = Math.Min(
            FindTourDistance(first + 1, second) + Distance(first, first + 1),
            FindTourDistance(first + 1, first) + Distance(second, first + 1)
        );

        return _dp[first, second];
    }

    public double FindBitonicTSP()
    {
        int lastPointIndex = _points.Count - 1;
        InitializeDp();

        for (int i = 0; i < lastPointIndex - 1; i++)
        {
            _dp[lastPointIndex - 1, i] = Distance(lastPointIndex - 1, lastPointIndex) + 
                                           Distance(i, lastPointIndex);
        }

        return FindTourDistance(0, 0);
    }

    private void InitializeDp()
    {
        int length = _points.Count;
        _dp = new double[length, length];

        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                _dp[i, j] = -1;
            }
        }
    }

    private struct Point
    {
        public readonly int x;
        public readonly int y;

        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }
}
