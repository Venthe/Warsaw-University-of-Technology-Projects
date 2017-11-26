using System;
using System.Collections.Generic;

namespace MultiLayeredPerceptron {
   public class Layer {
      public Layer(int layerInputsCount, int layerSize, LayerType layerType) {
         this.LayerType = layerType;
         this.InputNodeCount = layerInputsCount;

         this.PopulatePerceptrons(layerInputsCount, layerSize);
      }

      private IList<Perceptron> Perceptrons { get; } = new List<Perceptron>();
      public LayerType LayerType { get; }
      public int InputNodeCount { get; }

      private void PopulatePerceptrons(int layerInputsCount, int layerSize) {
         for (var i = 0; i < layerSize; i++) {
            this.Perceptrons.Add(new Perceptron(layerInputsCount));
         }
      }

      public List<double> Train(IList<double> trainingEntry, Func<double, double> activationFunction) {
         var results = new List<double>();
         foreach (var perceptron in this.Perceptrons) {
            results.Add(perceptron.Classify(trainingEntry, activationFunction));
         }

         return results;
      }
   }
}
