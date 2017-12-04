using System;
using System.Collections.Generic;
using System.Linq;

namespace MultiLayeredPerceptron
{
   public class LayerDefinition
   {
      public int SizeWithBias { get; private set; }
      public int SizeWithoutBias { get; private set; }
      public LayerType Type { get; private set; }
      public int InputsCount { get; private set; }

      public LayerDefinition OfType(LayerType type)
      {
         Type = type;
         return this;
      }

      public LayerDefinition WithSize(int size)
      {
         SizeWithoutBias = size;

         return this;
      }

      public LayerDefinition WithBias()
      {
         if (Type.Equals(LayerType.Output))
            throw new InvalidOperationException($"Layer type must not equal {LayerType.Output} to have bias");

         if (SizeWithoutBias.Equals(null))
            throw new InvalidOperationException("To count layer size with bias it must have a size first");

         SizeWithBias = SizeWithoutBias + 1;
         return this;
      }

      public LayerDefinition WithInputCount(int inputsCount)
      {
         InputsCount = inputsCount;
         return this;
      }

      public int GetSize()
      {
         if (Type.Equals(LayerType.Hidden))
            return SizeWithoutBias;
         if (SizeWithBias.Equals(null))
            throw new ArgumentNullException("You must provide size with bias first");

         return SizeWithBias;
      }
   }

   public class LayersSize
   {
      public LayersSize(int inputLayerSize, int outputLayerSize, IList<int> hiddenLayersSize)
      {
         Definitions = PopulateDefinitions(inputLayerSize, outputLayerSize, hiddenLayersSize);

         Definitions = Definitions.Select((definition, i) =>
         {
            if (i == 0)
               return Definitions[i].WithInputCount(definition.GetSize());
            return Definitions[i].WithInputCount(Definitions[i].GetSize());
         }).ToList();
      }

      public IList<LayerDefinition> Definitions { get; } = new List<LayerDefinition>();

      private IList<LayerDefinition> PopulateDefinitions(int inputLayerSize, int outputLayerSize,
         IList<int> hiddenLayersSize)
      {
         var result = new List<LayerDefinition>();

         result.Add(new LayerDefinition()
            .OfType(LayerType.Input)
            .WithSize(inputLayerSize)
            .WithBias());

         hiddenLayersSize.ToList()
            .ForEach(layerSize =>
               result.Add(new LayerDefinition()
                  .OfType(LayerType.Hidden)
                  .WithSize(layerSize)
                  .WithBias()));

         result.Add(new LayerDefinition()
            .OfType(LayerType.Output)
            .WithSize(outputLayerSize));

         return result;
      }
   }

   public class LayersDefinition
   {
      public LayersDefinition(IList<string> inputLabels, IList<string> outputLabels, IList<int> hiddenLayersSizes)
      {
         LayersSizes = new LayersSize(inputLabels.Count, outputLabels.Count, hiddenLayersSizes);
         Layers = PopulateLayers(LayersSizes);

         InputLabels = inputLabels;
         OutputLabels = outputLabels;
      }

      public IList<string> InputLabels { get; }
      public IList<string> OutputLabels { get; }
      public LayersSize LayersSizes { get; }
      public IList<Layer> Layers { get; }

      private IList<Layer> PopulateLayers(LayersSize layersSize)
      {
         return LayersSizes.Definitions
            .Select(layerDefinition => new Layer(layerDefinition))
            .ToList();
      }

      private static IList<int> getNetworkSizes(IList<string> inputNodeLabels, IList<string> outputNodeLabels,
         IList<int> hiddenLayers)
      {
         var sizes = new List<int>();

         sizes.AddRange(hiddenLayers);
         sizes.Add(outputNodeLabels.Count());

         return sizes;
      }
   }
}