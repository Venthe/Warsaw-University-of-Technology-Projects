using System.Collections.Generic;

namespace MultiLayeredPerceptron
{
   public interface ILayersDefinition
   {
      IList<string> InputLabels { get; }
      IEnumerable<Layer> Layers { get; }
      IList<string> OutputLabels { get; }
   }
}