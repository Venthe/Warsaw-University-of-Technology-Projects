using System;

namespace MultiLayeredPerceptron.Extensions
{
   internal static class DoubleExtension
   {
      private static Random Rng { get; } = new Random();

      public static double GetRandomNumber(double minimum, double maximum)
      {
         return Rng.NextDouble() * (maximum - minimum) + minimum;
      }

      public static double BoolToDouble(bool sigmoidValue)
      {
         return sigmoidValue ? 1 : 0;
      }

      public static string ToNonEString(this double value)
      {
         return $"{value:F20}";
      }
   }
}