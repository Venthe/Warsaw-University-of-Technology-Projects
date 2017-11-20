using System.Collections.Generic;

using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron.Network {
   public class PerceptronInput {
      public PerceptronInput() {
         this.value = DoubleExtension.GetRandomNumber(-1, 1);
         this.weight = DoubleExtension.GetRandomNumber(-2, 2);
      }

      public PerceptronInput(double value, double weight) {
         this.value = value;
         this.weight = weight;
      }

      public double value { get; }
      public double weight { get; }

      public override string ToString() => $"[v:{this.value}|w:{this.weight}]";

      public static string ToString(IEnumerable<PerceptronInput> perceptronInputs) => string.Join(",", perceptronInputs);
   }
}
