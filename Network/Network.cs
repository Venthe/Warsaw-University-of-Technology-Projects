using System;
using System.Collections.Generic;
using System.Linq;

using MultiLayeredPerceptron.Extensions;
using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron {
   public class Network {
      public IList<string> InputLabels { get; }
      public IList<string> OutputLabels { get; }
      public IList<Layer> layers { get; }
      public Func<double, double> ActivationFunction { get; }
      public Boolean Verbose { get; set; } = false;
      public bool Backpropagate { get; set; } = false;

      public Network(IList<string> inputNodeLabels, IList<string> outputNodeLabels, IList<int> hiddenLayers, Func<double, double> activationFunction) {
         this.InputLabels = inputNodeLabels;
         this.OutputLabels = outputNodeLabels;

         this.layers = this.PopulateLayers(inputNodeLabels, outputNodeLabels, hiddenLayers);

         this.ActivationFunction = activationFunction;
      }

      private IList<Layer> PopulateLayers(IList<string> inputNodeLabels, IList<string> outputNodeLabels, IList<int> hiddenLayers) {
         var networkSizes = setNetworkSizes(inputNodeLabels, outputNodeLabels, hiddenLayers);
         var list = new List<Layer>();

         for (var i = 0; i < networkSizes.Count; i++) {
            if (i == 0) {
               list.Add(new Layer(inputNodeLabels.Count(), networkSizes[i], LayerType.First));
            } else {
               list.Add(new Layer(networkSizes[i - 1], networkSizes[i], LayerType.Hidden));
            }
         }

         return list;
      }

      private static IList<int> setNetworkSizes(IList<string> inputNodeLabels, IList<string> outputNodeLabels, IList<int> hiddenLayers) {
         var sizes = new List<int>();

         sizes.AddRange(hiddenLayers);
         sizes.Add(outputNodeLabels.Count());

         return sizes;
      }

      public void Train(TrainingSet trainingSet) {
         Console.WriteLine("\t* Starting training");
         var trainingResults = new List<IList<Result>>();

         foreach (var trainingEntry in trainingSet.TrainingEntries) {
            if (Verbose) {
               this.PresentHeaderForSet(trainingEntry);
            }
            var result = this.TrainWithSet(trainingEntry);
            if (Verbose) {
               this.PresentFooterForSet(result, trainingEntry);
            }
            trainingResults.Add(result);
         }

         if (Backpropagate) {
            Console.WriteLine("\t* Backpropagating...");
            // TODO: Backpropagate
         }

         Console.WriteLine("\t* Finished training");
      }

      private IList<Result> TrainWithSet(ITrainingEntry trainingEntry) {
         var trainingResultForEntry = new List<IList<double>> {trainingEntry.Inputs};
         var j = 0;
         foreach (var layer in this.layers) {
            var trainingData = trainingResultForEntry[j];
            var resultsForLayer = layer.Train(trainingData, this.ActivationFunction);
            trainingResultForEntry.Add(resultsForLayer);
            j++;
         }

         var resultValues = trainingResultForEntry.Last();
         var resultErrors = trainingEntry.CalculateError(resultValues);
         var results = new List<Result>();
         for (var i = 0; i < trainingEntry.Labels.Count; i++) {
            var result = new Result(resultValues[i], resultErrors[i]);
            results.Add(result);
         }

         return results;
      }

      private void PresentFooterForSet(IList<Result> results, ITrainingEntry trainingEntry) {
         Console.WriteLine("- set completed");
         for (var i = 0; i < this.OutputLabels.Count(); i++) {
            Console.WriteLine($"{this.OutputLabels[i]}: {results[i] .Value.ToNonEString()} with error {results[i] .Error.ToNonEString()}");
         }
      }

      private void PresentHeaderForSet(ITrainingEntry trainingEntry) {
         Console.WriteLine("- Start set");
         for (var i = 0; i < this.InputLabels.Count(); i++) {
            Console.WriteLine($"\t{this.InputLabels[i]}: {trainingEntry.Inputs[i]}");
         }

         Console.WriteLine($"\tExpected: {trainingEntry.Labels[0]}");
      }
   }
}
