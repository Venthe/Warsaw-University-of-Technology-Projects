using System;
using System.Collections.Generic;
using System.Linq;

using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron.Network {
   public enum LayerType {
      First,
      Hidden
   }

   public class Layer {
      private IList<Perceptron> Perceptrons { get; } = new List<Perceptron>();
      public IList<double> Results { get; } = new List<double>();
      private Func<double, double> ActivationFunction { get; }
      public LayerType LayerType { get; }

      public Layer(int layerInputsCount, int layerSize, Func<double, double> activationFunction, LayerType layerType) {
         this.LayerType = layerType;

         this.ActivationFunction = activationFunction;

         for (var i = 0; i < layerSize; i++) {
            this.Perceptrons.Add(new Perceptron(layerInputsCount, activationFunction));
         }
      }

      public double Train(TrainingEntry trainingEntry) {
         double result = 0;
         foreach (var perceptron in this.Perceptrons) {
            result += perceptron.Classify(trainingEntry)
                                .Result;
         }

         this.Results.Add(result);

         return result;
      }

      public double Result() => this.Results.Sum() / this.Results.Count;
   }
}
