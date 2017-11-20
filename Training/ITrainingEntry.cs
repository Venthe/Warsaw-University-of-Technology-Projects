using System.Collections.Generic;

namespace MultiLayeredPerceptron.Training {
   public interface ITrainingEntry {
      IEnumerable<double> GetInputs();

      string ToString();
   }
}
