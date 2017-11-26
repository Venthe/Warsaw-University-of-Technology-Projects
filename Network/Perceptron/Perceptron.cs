using System;
using System.Collections.Generic;
using System.Linq;

using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron {
   public class Perceptron: IPerceptron {
      private readonly IList<double> _weights;

      public Perceptron(int inputsCount) {
         ValidateAtLeastOneInput(inputsCount);

         this._weights = PopulateWeights(inputsCount);
      }

      public double Result { get; private set; }

      public double CalculateError(double expectedValue) => expectedValue - this.Result;

      public double Classify(IList<double> trainingEntry, Func<double, double> activationFunction) {
         var guess = this.CalculateGuess(trainingEntry);
         var result = activationFunction(guess);
         return result;
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

      private double CalculateGuess(IList<double> trainingEntry) => trainingEntry.Select((inputValue, index) => inputValue * this._weights[index])
                                                                                 .Sum();
   }
}
