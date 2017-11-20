using System.Collections.Generic;

using MultiLayeredPerceptron.Extensions;

namespace MultiLayeredPerceptron.Training {
   public class TrainingSet {
      private readonly IList<TrainingEntry> _trainingEntries = new List<TrainingEntry>();

      public TrainingSet(int entriesCount) {
         for (var i = 0; i < entriesCount; i++) {
            this._trainingEntries.Add(new TrainingEntry(DoubleExtension.GetRandomNumber(-10, 10), DoubleExtension.GetRandomNumber(-10, 10)));
         }
      }

      public IList<TrainingEntry> GetEntries() => this._trainingEntries;

      public ITrainingEntry GetTrainingEntry(int index) => this._trainingEntries[index];

      public override string ToString() => ListExtensions.ToString(this._trainingEntries);
   }
}
