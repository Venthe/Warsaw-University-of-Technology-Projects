namespace MultiLayeredPerceptron.Network {
   public class Node {
      public Node(string name) {
         this.Name = name;
         this.Value = double.NaN;
      }

      public string Name { get; }
      public double Value { get; }

      public override string ToString() => $"[{this.Name}|{this.Value}]";
   }
}
