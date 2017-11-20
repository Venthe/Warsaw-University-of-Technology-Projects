using System;
using System.Collections.Generic;

using MultiLayeredPerceptron.Network;
using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron {
   internal class Program {
      private static void Main(string[] args) {
         var inputLabels = new List<string> {"x", "y"};
         var hiddenLayerCount = new List<int> {3, 4, 3};
         var outputLabels = new List<string> {"valid", "invalid"};
         var trainingSet = new TrainingSet(10);

         var network = new NetworkModel(inputLabels, outputLabels, hiddenLayerCount, ActivationFunction.Sigmoid);
         network.Train(trainingSet);
      }
   }
}
