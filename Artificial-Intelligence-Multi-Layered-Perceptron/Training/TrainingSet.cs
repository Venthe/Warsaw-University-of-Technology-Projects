using System.Collections.Generic;
using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron.Training
{
   public class TrainingSet
   {
      public TrainingSet(int entriesCount, IList<string> labels)
      {
         for (var i = 0;
            i < entriesCount;
            i++) // TODO Training set is now statically set to very simple problem (x, y, is it above the line) and thus it's constructor is garbage
            TrainingEntries.Add(new AboveLineTrainingEntry(DoubleExtension.GetRandomNumber(-10, 10),
               DoubleExtension.GetRandomNumber(-10, 10), labels[0]));
      }

      public IList<ITrainingEntry> TrainingEntries { get; } = new List<ITrainingEntry>();

      public override string ToString()
      {
         return ListExtensions.ToString(TrainingEntries);
      }
   }
}