namespace MultiLayeredPerceptron.Training
{
   public class Label
   {
      public Label(string name, double value)
      {
         Name = name;
         Value = value;
      }

      public string Name { get; }
      public double Value { get; }
   }
}