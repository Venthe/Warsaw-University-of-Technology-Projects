namespace MultiLayeredPerceptron
{
   public interface IActivationFunction
   {
      double Function(double value);

      double Derivative(double value);
   }
}