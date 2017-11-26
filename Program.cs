using System;
using System.Collections.Generic;

using MultiLayeredPerceptron;
using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron {
   internal class Program {
      private static void Main(string[] args) {
         var inputLabels = new List<string> {"x", "y"};
         var hiddenLayerCount = new List<int> {3, 4, 3};
         var outputLabels = new List<string> {"Above the line"};
         var trainingSet = new TrainingSet(10, outputLabels);
         var network = new Network(inputLabels, outputLabels, hiddenLayerCount, ActivationFunctions.Sigmoid.Function);


         ConsoleKeyInfo cki;
         do
         {
            Console.WriteLine("t) train \nb) set backpropagation \nv) set verbose");
            cki = Console.ReadKey(false);
            Console.WriteLine();
            switch (cki.KeyChar.ToString())
            {
               case "t":
                  network.Train(trainingSet);
                  break;
               case "b":
                  network.Backpropagate = !network.Backpropagate;
                  Console.WriteLine($"Backpropagate set to {network.Backpropagate}");
                  break;
               case "v":
                  network.Verbose = !network.Verbose;
                  Console.WriteLine($"Verbose mode set to {network.Verbose}");
                  break;
            }
         } while (cki.Key != ConsoleKey.Escape);


         Console.ReadKey();
      }
   }
}
