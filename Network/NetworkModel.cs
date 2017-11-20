using System;
using System.Collections.Generic;
using System.Linq;

using MultiLayeredPerceptron.Extensions;
using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron.Network {
   public class NetworkModel {
      public IEnumerable<string> InputLabels;
      public IEnumerable<string> OutputLabels;
      public IList<Layer> layers { get; } = new List<Layer>();
      public Func<double, double> ActivationFunction { get; }

      public NetworkModel(IEnumerable<string> inputNodeLabels, IEnumerable<string> outputNodeLabels, IEnumerable<int> hiddenLayers, Func<double, double> activationFunction) {
         this.InputLabels = inputNodeLabels;
         this.OutputLabels = outputNodeLabels;

         this.layers = this.PopulateLayers(inputNodeLabels, outputNodeLabels, hiddenLayers, activationFunction);

         this.ActivationFunction = activationFunction;
      }

      private IList<Layer> PopulateLayers(IEnumerable<string> inputNodeLabels, IEnumerable<string> outputNodeLabels, IEnumerable<int> hiddenLayers, Func<double, double> activationFunction) {
         var networkSizes = setNetworkSizes(inputNodeLabels, outputNodeLabels, hiddenLayers);
         var list = new List<Layer>();

         for (var i = 0; i < networkSizes.Count; i++) {
            if (i == 0) {
               list.Add(new Layer(inputNodeLabels.Count(), networkSizes[i], activationFunction, LayerType.First));
            } else {
               list.Add(new Layer(networkSizes[i - 1], networkSizes[i], activationFunction, LayerType.Hidden));
            }
         }

         return list;
      }

      private static IList<int> setNetworkSizes(IEnumerable<string> inputNodeLabels, IEnumerable<string> outputNodeLabels, IEnumerable<int> hiddenLayers) {
         var sizes = new List<int>();

         sizes.AddRange(hiddenLayers);
         sizes.Add(outputNodeLabels.Count());

         return sizes;
      }

      public override string ToString() => $"__Network__\n{ListExtensions.ToString(this.InputLabels)}\n{ListExtensions.ToString(this.OutputLabels)}";

      public void Train(TrainingSet trainingSet) {
//         IList<double> trainingResult = new List<double>();

         foreach (var trainingEntry in trainingSet.GetEntries()) {
            foreach (var layer in this.layers) {
//               if (layer.LayerType == LayerType.First) {
//                  continue;
//               }

               layer.Train(trainingEntry);
//               trainingResult.Add(layer.Results);
               Console.WriteLine(ListExtensions.ToString(layer.Results));
            }
         }
      }
   }
}
