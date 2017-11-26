using System.Collections;
using System.Collections.Generic;

using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron.Training {
   public class AboveLineTrainingEntry: ITrainingEntry {
      public AboveLineTrainingEntry(double x, double y, string lbl) {
         // Test example; "Valid line" is x=y
         this.Labels.Add(DoubleExtension.BoolToDouble(y >= x));

         this.Inputs.Add(x);
         this.Inputs.Add(y);
      }

      public IList<double> Inputs { get; } = new List<double>();
      public IList<double> Labels { get; } = new List<double>();

      public IList<double> CalculateError(IList<double> results) {
         var errors = new List<double>();
         for (var i = 0; i < this.Labels.Count; i++) {
            errors.Add(results[i] - this.Labels[i]);
         }

         return errors;
      }
   }
}
