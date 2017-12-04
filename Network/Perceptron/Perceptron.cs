using System;
using System.Collections.Generic;
using System.Linq;
using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron
{
   public class Perceptron : IPerceptron
   {
      private readonly IList<double> _weights;

      public Perceptron(int inputsCount)
      {
         ValidateAtLeastOneInput(inputsCount);

         var inputsCountWithBias = inputsCount + 1;

         _weights = PopulateWeights(inputsCountWithBias);
      }

      public double Result { get; private set; }

      public double CalculateError(double expectedValue)
      {
         return expectedValue - Result;
      }

      public double Classify(IList<double> trainingEntry, Func<double, double> activationFunction)
      {
         var trainingEntryWithBias = getTrainingEntryWithBias(trainingEntry);

         var guess = CalculateGuess(trainingEntryWithBias);
         var result = activationFunction(guess);
         return result;
      }

      private IList<double> getTrainingEntryWithBias(IList<double> trainingEntry)
      {
         trainingEntry.Add(1.0);

         return trainingEntry;
      }

      private static IList<double> PopulateWeights(int inputsCount)
      {
         var list = new List<double>();
         for (var i = 0; i < inputsCount; i++) list.Add(GetInitialWeight());

         return list;
      }

      private static void ValidateAtLeastOneInput(int inputsCount)
      {
         if (inputsCount == 0) throw new ArgumentException();
      }

      private static double GetInitialWeight()
      {
         return DoubleExtension.GetRandomNumber(-5, 5);
      }

      private double CalculateGuess(IList<double> trainingEntry)
      {
         return trainingEntry.Select((inputValue, index) => inputValue * _weights[index])
            .Sum();
      }
   }
}