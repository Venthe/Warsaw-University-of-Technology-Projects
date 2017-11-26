using System;

namespace MultiLayeredPerceptron.Extensions {
   internal static class DoubleExtension {
      private static Random Rng { get; } = new Random();

      public static double GetRandomNumber(double minimum, double maximum) => Rng.NextDouble() * (maximum - minimum) + minimum;

      public static double BoolToDouble(bool sigmoidValue) => sigmoidValue ? 1 : 0;

      public static string ToNonEString(this double value) => $"{value:F20}";
   }
}
