using System;
using System.Collections.Generic;
using MultiLayeredPerceptron.Training;

namespace MultiLayeredPerceptron
{
   internal class Program
   {
      private static void Main()
      {
         var inputLabels = new List<string> {"x", "y"};
         var hiddenLayerCount = new List<int> {3, 4, 3};
         var outputLabels = new List<string> {"Above the line"};
         var trainingSet = new TrainingSet(10, outputLabels);
         var network = new Network(inputLabels, outputLabels, hiddenLayerCount, ActivationFunctions.Sigmoid.Function);

         ConsoleKeyInfo consoleKeyInfo;
         do
         {
            Console.WriteLine("t) train \nb) set backpropagation \nv) set verbose");
            consoleKeyInfo = Console.ReadKey(false);
            Console.WriteLine();
            switch (consoleKeyInfo.KeyChar.ToString())
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
         } while (consoleKeyInfo.Key != ConsoleKey.Escape);

         Console.ReadKey();
      }
   }
}