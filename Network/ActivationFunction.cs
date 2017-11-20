using System;

namespace MultiLayeredPerceptron.Network {
   public static class ActivationFunction {
      public static double Sigmoid(double value) => Math.Pow(Math.E, value) / (Math.Pow(Math.E, value) + 1);
   }
}
