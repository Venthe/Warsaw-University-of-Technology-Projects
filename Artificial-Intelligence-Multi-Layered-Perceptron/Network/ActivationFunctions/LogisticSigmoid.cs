using System;

namespace MultiLayeredPerceptron
{
   public class LogisticSigmoid : IActivationFunction
   {
      public double Function(double value)
      {
         return 1 / (1 + Math.Exp(-value));
      }

      public double Derivative(double value)
      {
         return Function(value) * (1 - Function(value));
      }
   }
}