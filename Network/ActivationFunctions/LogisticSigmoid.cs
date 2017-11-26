using System;

namespace MultiLayeredPerceptron {
   public class LogisticSigmoid: IActivationFunction {
      public double Function(double value) => 1 / (1 + Math.Exp(-value));

      public double Derivative(double value) => this.Function(value) * (1 - this.Function(value));
   }
}