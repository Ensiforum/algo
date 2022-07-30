using System;

namespace algo
{
    public class continuous_knapsack
    {
        public static double FindMax(int[] prices, int[] weights, int maxWeight)
        {
            if (prices.Length != weights.Length)
            {
                throw new ArgumentException();
            }
            
            var items = new Item[prices.Length];
            for (int i = 0; i < items.Length; i++)
            {
                items[i] = new Item(prices[i], weights[i]);
            }
            Array.Sort(items);
            
            double currentCost = 0;
            double currentWeight = 0;

            for (int i = items.Length - 1; i >= 0 && currentWeight < maxWeight; i--)
            {
                if (currentWeight + items[i].weight < maxWeight)
                {
                    currentCost += items[i].price;
                    currentWeight += items[i].weight;
                }
                else
                {
                    currentCost += items[i].SpecificCost * (maxWeight - currentWeight);
                    currentWeight = maxWeight;
                }
            }

            return currentCost;
        }

        private class Item : IComparable
        {
            public int price;

            public Item(int price, int weight)
            {
                this.price = price;
                this.weight = weight;
            }

            public int weight;
            public double SpecificCost => price / (double) weight;
            
            public int CompareTo(object obj)
            {
                if (!(obj is Item))
                {
                    throw new ArgumentException();
                }

                if (SpecificCost > ((Item) obj).SpecificCost)
                {
                    return 1;
                }
                if (Math.Abs(SpecificCost - ((Item) obj).SpecificCost) < 1e-7)
                {
                    return 0;
                }

                return -1;
            }
        }
    }
}