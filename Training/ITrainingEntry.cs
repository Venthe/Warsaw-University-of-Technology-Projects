using System.Collections.Generic;

namespace MultiLayeredPerceptron.Training
{
   public interface ITrainingEntry
   {
      IList<double> Inputs { get; }
      IList<double> Labels { get; }
      IList<double> CalculateError(IList<double> results);
   }
}