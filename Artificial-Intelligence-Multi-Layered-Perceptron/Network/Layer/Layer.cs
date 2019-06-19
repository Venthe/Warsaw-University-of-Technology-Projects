using System;
using System.Collections.Generic;

namespace MultiLayeredPerceptron
{
   public class Layer
   {
      private IList<Perceptron> Perceptrons { get; } = new List<Perceptron>();
      public LayerType LayerType { get; }
      public int InputNodeCount { get; }

      public Layer(LayerDefinition layerDefinition)
      {
         Perceptrons = this.PopulatePerceptrons(layerDefinition);
      }

      private IList<Perceptron> PopulatePerceptrons(LayerDefinition layerDefinition)
      {
         var perceptrons = new List<Perceptron>();
         for (var i = 0; i < layerDefinition.GetSize(); i++)
         {
            perceptrons.Add(new Perceptron(layerDefinition.InputsCount));
         }
         return perceptrons;
      }

      public List<double> Train(IList<double> trainingEntry, Func<double, double> activationFunction)
      {
         var results = new List<double>();
         foreach (var perceptron in Perceptrons) results.Add(perceptron.Classify(trainingEntry, activationFunction));

         return results;
      }
   }
}