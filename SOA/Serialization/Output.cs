using System;
using System.Linq;

namespace Serialization
{
    public class Output
    {
        public Output()
        {
            SumResult = SumResult;
            MulResult = MulResult;
            SortedInputs = SortedInputs;
        }
        public Output(Input input)
        {
            SumResult = input.Sums.Sum() * input.K;
            MulResult = input.Muls.Aggregate(1, (a, b) => a * b);
            SortedInputs = input.Sums
                .Concat(input.Muls.Select(Convert.ToDecimal))
                .OrderBy(t => t)
                .ToArray();
        }
        public decimal SumResult { get; set; }
        public int MulResult { get; set; }
        public decimal[] SortedInputs { get; set; }
    }
}