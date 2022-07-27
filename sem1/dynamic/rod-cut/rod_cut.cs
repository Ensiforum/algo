// Written by Oleksandr Pravosud

using System.Collections.Generic;

public class RodCut
{
    public readonly int MaximalPrice;
    public readonly int[] CutSolution;
    
    private readonly int[] _prices;
    private readonly int[] _results;
    private readonly int[] _splits;
    private readonly int _n;

    public RodCut(int[] prices)
    {
        _prices = prices;
        _n = prices.Length;
        _results = new int[_n + 1];
        _splits = new int[_n + 1];
        
        MaximalPrice = Cut();
        CutSolution = Solution();
    }

    private int Cut()
    {
        _results[0] = 0;
        for (int i = 1; i < _n + 1; i++)
        {
            int result = -1;
            for (int j = 1; j < i + 1; j++)
            {
                int candidate = _prices[j - 1] + _results[i - j];
                if (candidate > result)
                {
                    result = candidate;
                    _splits[i] = j;
                }
            }

            _results[i] = result;
        }

        return _results[_n];
    }

    private int[] Solution()
    {
        List<int> result = new List<int>();
        int size = _n;
        while (size > 0)
        {
            result.Add(_n);
            size -= _splits[size];
        }

        return result.ToArray();
    }
}
