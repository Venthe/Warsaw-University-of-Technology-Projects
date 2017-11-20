using System.Collections.Generic;

using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron.Training {
   public class TrainingEntry: ITrainingEntry {
      private readonly bool isValid;
      private readonly double x;
      private readonly double y;

      public TrainingEntry(double x, double y) {
         this.x = x;
         this.y = y;

         // Test example; "Valid line" is x=y
         this.isValid = y >= x;
      }

      public IEnumerable<double> GetInputs() => new[] {this.x, this.y};

      public override string ToString() => $"[{this.x},{this.y}|{this.isValid}]";

      public double ExpectedValue() => DoubleExtension.BoolToDouble(this.isValid);
   }
}
