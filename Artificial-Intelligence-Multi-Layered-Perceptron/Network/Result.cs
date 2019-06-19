namespace MultiLayeredPerceptron
{
   public class Result
   {
      public Result(double value, double error)
      {
         Value = value;
         Error = error;
      }

      public double Value { get; }
      public double Error { get; }
   }
}