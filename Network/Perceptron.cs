using System;
using System.Collections.Generic;
using System.Linq;

using MultiLayeredPerceptron.Extensions;
using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron.Network {
   public class Perceptron: IPerceptron {
      private readonly IList<double> _weights;
      private readonly Func<double, double> _activationFunction;
      public double Result { get; private set; }

      public Perceptron(int inputsCount, Func<double, double> activationFunction) {
         ValidateAtLeastOneInput(inputsCount);
         this._activationFunction = activationFunction;

         this._weights = PopulateWeights(inputsCount);
      }

      public double CalculateError(double expectedValue) => expectedValue - this.Result;

      public Perceptron Classify(ITrainingEntry trainingEntry) {
         this.ValidateWeightsAndInputValuesCountMatch(trainingEntry);

         this.Result = this._activationFunction(this.CalculateGuess(trainingEntry));

         return this;
      }

      private static IList<double> PopulateWeights(int inputsCount) {
         var list = new List<double>();
         for (var i = 0; i < inputsCount; i++) {
            list.Add(GetInitialWeight());
         }

         return list;
      }

      private static void ValidateAtLeastOneInput(int inputsCount) {
         if (inputsCount == 0) {
            throw new ArgumentException();
         }
      }

      private static double GetInitialWeight() => DoubleExtension.GetRandomNumber(-5, 5);

      private void ValidateWeightsAndInputValuesCountMatch(ITrainingEntry trainingEntry) {
         if (!Equals(trainingEntry.GetInputs()
                                  .Count(), this._weights.Count)) {
            throw new ArgumentException();
         }
      }

      private double CalculateGuess(ITrainingEntry trainingEntry) => trainingEntry.GetInputs()
                                                                                  .Select((inputValue, index) => inputValue * this._weights[index])
                                                                                  .Sum();
   }
}
