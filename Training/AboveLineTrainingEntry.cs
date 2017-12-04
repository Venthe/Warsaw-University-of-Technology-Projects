using System.Collections.Generic;
using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron.Training
{
   public class AboveLineTrainingEntry : ITrainingEntry
   {
      public AboveLineTrainingEntry(double x, double y, string lbl)
      {
         // Test example; "Valid line" is x=y
         Labels.Add(DoubleExtension.BoolToDouble(y >= x));

         Inputs.Add(x);
         Inputs.Add(y);
      }

      public IList<double> Inputs { get; } = new List<double>();
      public IList<double> Labels { get; } = new List<double>();

      public IList<double> CalculateError(IList<double> results)
      {
         var errors = new List<double>();
         for (var i = 0; i < Labels.Count; i++) errors.Add(results[i] - Labels[i]);

         return errors;
      }
   }
}