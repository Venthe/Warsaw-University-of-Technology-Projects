using System;
using System.Collections.Generic;
using System.Linq;
using MultiLayeredPerceptron.Extensions;
using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron
{
   public class Network
   {
      public Network(IList<string> inputNodeLabels, IList<string> outputNodeLabels, IList<int> hiddenLayersDefinition,
         Func<double, double> activationFunction)
      {
         ActivationFunction = activationFunction;

         this.Definition = new LayersDefinition(inputNodeLabels, outputNodeLabels, hiddenLayersDefinition);
      }

      public Func<double, double> ActivationFunction { get; }
      public ILayersDefinition Definition { get; }
      public bool Verbose { get; set; } = false;
      public bool Backpropagate { get; set; } = false;

      public void Train(TrainingSet trainingSet)
      {
         Console.WriteLine("\t* Starting training");
         var trainingResults = new List<IList<Result>>();

         foreach (var trainingEntry in trainingSet.TrainingEntries)
         {
            if (Verbose) PresentHeaderForSet(trainingEntry);
            var result = TrainWithSet(trainingEntry);
            if (Verbose) PresentFooterForSet(result, trainingEntry);
            trainingResults.Add(result);
         }

         if (Backpropagate) Console.WriteLine("\t* Backpropagating...");

         Console.WriteLine("\t* Finished training");
      }

      private IList<Result> TrainWithSet(ITrainingEntry trainingEntry)
      {
         var trainingResultForEntry = new List<IList<double>> {trainingEntry.Inputs};
         var j = 0;
         foreach (var layer in this.Layers)
         {
            var trainingData = trainingResultForEntry[j];
            var resultsForLayer = layer.Train(trainingData, ActivationFunction);
            trainingResultForEntry.Add(resultsForLayer);
            j++;
         }

         var resultValues = trainingResultForEntry.Last();
         var resultErrors = trainingEntry.CalculateError(resultValues);
         var results = new List<Result>();
         for (var i = 0; i < trainingEntry.Labels.Count; i++)
         {
            var result = new Result(resultValues[i], resultErrors[i]);
            results.Add(result);
         }

         return results;
      }

      private void PresentFooterForSet(IList<Result> results, ITrainingEntry trainingEntry)
      {
         Console.WriteLine("- set completed");
         for (var i = 0; i < this.OutputLabels.Count(); i++)
            Console.WriteLine(
               $"{this.OutputLabels[i]}: {results[i].Value.ToNonEString()} with error {results[i].Error.ToNonEString()}");
      }

      private void PresentHeaderForSet(ITrainingEntry trainingEntry)
      {
         Console.WriteLine("- Start set");
         for (var i = 0; i < this.InputLabels.Count(); i++)
            Console.WriteLine($"\t{this.InputLabels[i]}: {trainingEntry.Inputs[i]}");

         Console.WriteLine($"\tExpected: {trainingEntry.Labels[0]}");
      }
   }
}