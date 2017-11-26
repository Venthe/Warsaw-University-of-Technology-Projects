namespace MultiLayeredPerceptron {
   public class Result {
      public Result(double value, double error)
      {
         this.Value = value;
         this.Error = error;
      }

      public double Value { get; }
      public double Error { get; }
   }
}