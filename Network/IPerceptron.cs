using System;

using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron.Network {
   public interface IPerceptron {
      double Result { get; }

      double CalculateError(double expectedValue);

      Perceptron Classify(ITrainingEntry trainingEntry);
   }
}
