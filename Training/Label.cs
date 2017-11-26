using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiLayeredPerceptron.Training
{
   public class Label {
      public Label(string name, double value)
      {
         Name = name;
         Value = value;
      }

      public string Name { get; }
      public double Value { get; }
   }
}
