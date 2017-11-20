using System.Collections.Generic;
using System.Linq;

namespace MultiLayeredPerceptron.Network {
   public class NodesSize {
      public NodesSize(IEnumerable<string> inputNodeLabels, IEnumerable<string> outputNodeLabels, IEnumerable<int> hiddenLayers) {
         this.Sizes.Add(inputNodeLabels.Count());

         foreach (var layerSize in hiddenLayers) {
            this.Sizes.Add(layerSize);
         }

         this.Sizes.Add(outputNodeLabels.Count());
      }

      private IList<int> Sizes { get; } = new List<int>();
   }
}
